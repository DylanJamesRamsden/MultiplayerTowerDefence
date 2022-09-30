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
	UPROPERTY(EditAnywhere)
	USphereComponent* DetectionRadiusComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
