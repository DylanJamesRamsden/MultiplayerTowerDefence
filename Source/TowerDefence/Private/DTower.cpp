// Fill out your copyright notice in the Description page of Project Settings.


#include "DTower.h"

// Sets default values
ADTower::ADTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretBaseMesh");
	BarrelBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelBaseMesh");
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");

	RootComponent = TurretBaseMesh;
	BarrelBaseMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetupAttachment(BarrelBaseMesh);
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

