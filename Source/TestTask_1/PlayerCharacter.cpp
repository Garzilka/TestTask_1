// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "NoughtsAndCrosses.h"
#include "GameFramework/SpringArmComponent.h"

#include "DrawDebugHelpers.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 900.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Camera->bUsePawnControlRotation = true;
	SpringArm->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult OutHit;
	APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	FVector Start = camManager->GetCameraLocation();
	FVector Forward = camManager->GetCameraRotation().Vector();
	FVector End = (Start + (Forward * 2000.f));

	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	if (isHit)
	{
		if (OutHit.bBlockingHit)
		{
			RefActor = Cast<ANoughtsAndCrosses>(OutHit.GetActor());
			if (RefActor != NULL)
			{
				RefActor->isSelect = true;
				//UE_LOG(LogTemp, Log, TEXT("Worked"))
			}
			//else UE_LOG(LogTemp, Log, TEXT("NWorked"))
		}
	}
	else RefActor = NULL;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RotateRMB", IE_Pressed, this, &APlayerCharacter::pressRightButton);
	PlayerInputComponent->BindAction("RotateRMB", IE_Released, this, &APlayerCharacter::releaseRightButton);
	PlayerInputComponent->BindAction("UseLMB", IE_Pressed, this, &APlayerCharacter::ClickLMB);
	//PlayerInputComponent->BindAction("UseLMB", IE_Released, this, &APlayerCharacter::releaseRightButton);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::GetMouseX);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::GetMouseY);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	FRotator F(SpringArm->GetRelativeRotation());
	FRotator A(F.Pitch, F.Yaw + b_MouseX,F.Roll);
	Camera->bUsePawnControlRotation = true;
	SpringArm->bUsePawnControlRotation = false;
	
	

	if (!isRMB)
	{
		Camera->bUsePawnControlRotation = true;
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	}
	else
	{
		Camera->bUsePawnControlRotation = false;
		SpringArm->SetRelativeRotation(A);
		
	}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	
	FRotator F(SpringArm->GetRelativeRotation());
	FRotator A(F.Pitch, F.Yaw, F.Roll);
	Camera->bUsePawnControlRotation = true;
	SpringArm->bUsePawnControlRotation = false;

	if (!isRMB)
	{
		Camera->bUsePawnControlRotation = true;
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
	else
	{
		Camera->bUsePawnControlRotation = false; 
		SpringArm->SetRelativeRotation(A); 
	}
}

void APlayerCharacter::pressRightButton()
{
	isRMB = true;
}

void APlayerCharacter::releaseRightButton()
{
	isRMB = false;
}

void APlayerCharacter::GetMouseX(float Rate)
{
	b_MouseX = Rate;
}

void APlayerCharacter::GetMouseY(float Rate)
{
	b_MouseY = Rate;
}

void APlayerCharacter::ClickLMB()
{
	if (RefActor != NULL)
	{
		RefActor->Enabled(true);
	}
}
