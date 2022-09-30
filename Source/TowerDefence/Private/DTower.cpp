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

	RootComponent = TurretBaseMeshComponent;
	BarrelBaseMeshComponent->SetupAttachment(RootComponent);
	BarrelMeshComponent->SetupAttachment(BarrelBaseMeshComponent);

	BarrelBaseMeshComponent->SetIsReplicated(true);
	BarrelMeshComponent->SetIsReplicated(true);

	DetectionRadiusComponent = CreateDefaultSubobject<USphereComponent>("DetectionRadiusComponent");
	DetectionRadiusComponent->SetupAttachment(RootComponent);

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

