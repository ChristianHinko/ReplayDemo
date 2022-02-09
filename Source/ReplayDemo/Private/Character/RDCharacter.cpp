// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/RDCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"



ARDCharacter::ARDCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Set our turn rates for input
	HorizontalSensitivity = 1.f;
	VerticalSensitivity = 1.f;

	// Don't rotate when the Controller rotates. Let that just affect the Camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Mesh defaults
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Create a CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 300.f;

	// Create a FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}


void ARDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Action
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ThisClass::OnJumpPressed);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Released, this, &ThisClass::OnJumpReleased);

	// Axis
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis(FName("HorizontalLook"), this, &ThisClass::HorizontalLook);
	PlayerInputComponent->BindAxis(FName("VerticalLook"), this, &ThisClass::VerticalLook);

}


// Actions

void ARDCharacter::OnJumpPressed()
{
	Jump();
}
void ARDCharacter::OnJumpReleased()
{
	StopJumping();
}


// Axis

void ARDCharacter::HorizontalLook(float Value)
{
	AddControllerYawInput(Value * HorizontalSensitivity * 0.5f);
}
void ARDCharacter::VerticalLook(float Value)
{
	AddControllerPitchInput(Value * VerticalSensitivity * 0.5f);
}

void ARDCharacter::MoveForward(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	const FRotator& YawRotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(YawRotator), Value);
}
void ARDCharacter::MoveRight(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	const FRotator& YawRotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(UKismetMathLibrary::GetRightVector(YawRotator), Value);
}
