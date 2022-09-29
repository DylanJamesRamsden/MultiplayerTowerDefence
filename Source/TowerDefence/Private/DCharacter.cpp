// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bUseControllerRotationYaw = true;

	// Creating components
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	// Setting up component attachment
	StaticMeshComponent->SetupAttachment(GetMesh());
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	StaticMeshComponent->SetWorldScale3D(FVector(0.25f, 0.25f, 0.5f));

	// Setting defaults on the SpringArmComponent
	SpringArmComponent->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 1200.0f;
	SpringArmComponent->bDoCollisionTest = false;

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
	AddMovementInput(GetActorForwardVector() * Value);
}

void ADCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Doing the rotation locally to prevent any delay when rotation your own character
	if (HasLocalNetOwner())
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FVector MouseWorldLocation;
			FVector MouseWorldDirection;
			PC->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

			// Using a line plane intersection rather than a line trace because I just find it simpler and nothing can
			// obstruct the line check (e.g. props such as a building)
			FVector PlaneIntersectionLocation = FMath::LinePlaneIntersection(MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * 10000),
				GetActorLocation(), FVector(0, 0, 1.0f));

			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlaneIntersectionLocation);

			// Use control rotation because the player controller is already repped, so there shouldn't be any major extra replication costs
			PC->SetControlRotation(LookRotation);
		}
	}
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);
}

void ADCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// When the character is possessed locally, we set it as the PlayerController's view target
	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		PC->SetViewTarget(this);
	}
}

