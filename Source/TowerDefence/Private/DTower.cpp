// Fill out your copyright notice in the Description page of Project Settings.


#include "DTower.h"

#include "Components/SphereComponent.h"

// Sets default values
ADTower::ADTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	TurretBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TurretBaseMeshComponent");
	BarrelBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BarrelBaseMeshComponent");
	BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMeshComponent");

	// This hierarchy is created achieve the expected behaviour:
	// 1. Allow the BarrelBaseMesh to control the yaw of the BarrelMesh
	// 2. Allow the BarrelMesh to control it's own pitch
	RootComponent = TurretBaseMeshComponent;
	BarrelBaseMeshComponent->SetupAttachment(RootComponent);
	BarrelMeshComponent->SetupAttachment(BarrelBaseMeshComponent);

	// The rotation of both the BarrelBaseMesh and BarrelMesh will need to replicate to clients
	BarrelBaseMeshComponent->SetIsReplicated(true);
	BarrelMeshComponent->SetIsReplicated(true);

	// Currently just using a SphereComponent as a way to detect things that walk into the radius (overlap with) of a
	// tower
	DetectionRadiusComponent = CreateDefaultSubobject<USphereComponent>("DetectionRadiusComponent");
	DetectionRadiusComponent->SetupAttachment(RootComponent);

	// By default the radius is set to 1200, its a good size for testing. But I am hoping to eventually throw all of
	// these values into a data table or data asset to control all of the values for all of the different types of towers
	DetectionRadiusComponent->SetSphereRadius(1200.0f);
}

// Called when the game starts or when spawned
void ADTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

