// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NoughtsAndCrosses_Manager.h"
#include "Materials/Material.h"
#include "NoughtsAndCrosses.generated.h"

UCLASS()
class TESTTASK_1_API ANoughtsAndCrosses : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoughtsAndCrosses();

	UBoxComponent* _Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OnMaterial)
		UMaterial* OnMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OnMaterial)
		UMaterial* OffMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Param, meta = (AllowPrivateAccess = "true"))
	int verticalPos = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Param, meta = (AllowPrivateAccess = "true"))
	int horizontalPos = 0;
	bool isUse = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Param, meta = (AllowPrivateAccess = "true"))
	bool isSelect = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
