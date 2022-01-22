// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "RDCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;



/**
 * Base Character
 */
UCLASS()
class REPLAYDEMO_API ARDCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;

public:
	ARDCharacter(const FObjectInitializer& ObjectInitializer);


	UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	float HorizontalSensitivity;
	float VerticalSensitivity;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Actions
	virtual void OnJumpPressed();
	virtual void OnJumpReleased();

	// Axis
	virtual void HorizontalLook(float Value);
	virtual void VerticalLook(float Value);

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

};
