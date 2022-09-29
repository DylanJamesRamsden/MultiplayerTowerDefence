// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOWERDEFENCE_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:
	// TMP: Just using as a place holder for now, so I can use a cube as our character mesh
	// @TODO Remove once we have a SkeletalMesh we want to use
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Moves the character either forwards or backwards, depending on if Value is 1 or -1
	void MoveForward(float Value);

	// Moves the character either right or left, depending on if Value is 1 or -1
	void MoveRight(float Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

};
