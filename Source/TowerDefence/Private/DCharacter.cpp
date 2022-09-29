// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "Components/ArrowComponent.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetMesh());
	StaticMeshComponent->SetWorldScale3D(FVector(0.25f, 0.25f, 0.5f));

	// TMP Just so I can see the forward direction with the temp cube as the character mesh
	// @TODO Remove this once we have a SkeletalMesh
	GetArrowComponent()->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector * Value);
}

void ADCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector * Value);
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);
}

