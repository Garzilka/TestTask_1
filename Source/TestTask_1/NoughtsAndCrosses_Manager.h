// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "NoughtsAndCrosses.h"
#include "NoughtsAndCrosses_Manager.generated.h"

UCLASS()
class TESTTASK_1_API ANoughtsAndCrosses_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoughtsAndCrosses_Manager();
	int Stats[5][5];
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void SpawnObjects();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
