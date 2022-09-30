// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DTower.generated.h"

UCLASS()
class TOWERDEFENCE_API ADTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADTower();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretBaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelBaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
