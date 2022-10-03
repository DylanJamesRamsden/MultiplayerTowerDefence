// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DTower.generated.h"

class USphereComponent;

UCLASS()
class TOWERDEFENCE_API ADTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADTower();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretBaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelBaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelMeshComponent;

	// Might sway away from using a USphereComponent eventually for handling a towers radius, just seems like the
	// simplest approach for now
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* DetectionRadiusComponent;

	// Stores a reference to the Enemy target in range
	UPROPERTY()
	AActor* EnemyTarget;

	// Determines whether or not to draw and print debug data for a turret
	UPROPERTY(EditAnywhere)
	bool bDebuggingEnabled = true;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnterDetectionRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnExitDetectionRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
