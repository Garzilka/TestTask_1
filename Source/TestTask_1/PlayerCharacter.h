// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NoughtsAndCrosses.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TESTTASK_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	ANoughtsAndCrosses* RefActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	float b_MouseX;
	float b_MouseY;

	
protected:
	
	virtual void BeginPlay() override;

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void pressRightButton();

	void releaseRightButton();

	void GetMouseX(float Rate);

	void GetMouseY(float Rate);

	void ClickLMB();

private:
	bool isRMB = false;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
