// Fill out your copyright notice in the Description page of Project Settings.


#include "DTower.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	DetectionRadiusComponent->OnComponentBeginOverlap.AddDynamic(this, &ADTower::OnEnterDetectionRadius);
	DetectionRadiusComponent->OnComponentEndOverlap.AddDynamic(this, &ADTower::OnExitDetectionRadius);
}

// Called every frame
void ADTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Leaving the rotation of the barrel and it's base to the server to just sync it up with all clients
	if (HasAuthority())
	{
		if (EnemyTarget)
		{
			// Using the world rotation as the current for the BarrelBaseMeshComponent
			FRotator BarrelBaseCurrentRotation = BarrelBaseMeshComponent->GetComponentRotation();
			// Using the relative rotation as the current for the BarrelMeshComponent as it needs to rotate with the
			// BarrelBaseMeshComponent and only adjust it's pitch
			FRotator BarrelCurrentRotation = BarrelMeshComponent->GetRelativeRotation();
		
			FRotator BarrelBaseLookRotation = UKismetMathLibrary::FindLookAtRotation(BarrelBaseMeshComponent->GetComponentLocation(),
				EnemyTarget->GetActorLocation());
			FRotator BarrelLookRotation = UKismetMathLibrary::FindLookAtRotation(BarrelMeshComponent->GetComponentLocation(),
				EnemyTarget->GetActorLocation());

			// When updating the rotation of the BarrelBaseMeshComponent, we update it's world rotation
			BarrelBaseMeshComponent->SetWorldRotation(FRotator(BarrelBaseCurrentRotation.Pitch, BarrelBaseLookRotation.Yaw, BarrelBaseCurrentRotation.Roll));
			// When updating the rotation of the BarrelMeshComponent, we update it's relative rotation as we want it to
			// still rotate relatively with the BarrelBaseMeshComponent 
			BarrelMeshComponent->SetRelativeRotation(FRotator(BarrelLookRotation.Pitch, BarrelCurrentRotation.Yaw, BarrelCurrentRotation.Roll));
		}
	}

	if (bDebuggingEnabled)
	{
		// Just some debug arrows to visualize the rotations being applied
		DrawDebugDirectionalArrow(GetWorld(), BarrelBaseMeshComponent->GetComponentLocation(),
			BarrelBaseMeshComponent->GetComponentLocation() + (BarrelBaseMeshComponent->GetForwardVector() * 300),5.0f, FColor::Purple);
		DrawDebugDirectionalArrow(GetWorld(), BarrelMeshComponent->GetComponentLocation(),
			BarrelMeshComponent->GetComponentLocation() + (BarrelMeshComponent->GetForwardVector() * 300),5.0f, FColor::Cyan);

		// Just a debug cylinder visualizing the turrets radius, TMP until I bring in a decal for a turrets radius
		DrawDebugCylinder(GetWorld(), GetActorLocation(), TurretBaseMeshComponent->GetComponentLocation(), DetectionRadiusComponent->GetScaledSphereRadius(),
			12.0f, FColor::Orange, false, -1, 0, 15.0f);	
	}
}

void ADTower::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Could only store the EnemyTarget on authority, but there may be some cosmetic stuff I want to do locally, so also
	// want to store it locally just in case
	// Also only setting enemy target if the tower does not have one.
	if (!EnemyTarget) EnemyTarget = OtherActor;
}

void ADTower::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (EnemyTarget)
	{
		// @TODO Need to queue up all enemies in range so if the tower does lose it's current enemy target, just pull one from the queue
		if (EnemyTarget == OtherActor) EnemyTarget = nullptr;
	}
}

