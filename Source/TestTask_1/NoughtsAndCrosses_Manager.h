// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "NoughtsAndCrosses.h"
//#include "NoughtsAndCrosses_AI.h"
#include "NoughtsAndCrosses_Manager.generated.h"

class NoughtsAndCrosses_AI;

UCLASS()
class TESTTASK_1_API ANoughtsAndCrosses_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoughtsAndCrosses_Manager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)//Можно сделать enum конечно, но нет
		int SettingAI;
	//Состояние сетки
	int Stats[5][5];
	//Ссылки кубов на сцене
	ANoughtsAndCrosses* _bCubes[5][5];
	//"Искуственный интеллект"
	NoughtsAndCrosses_AI* AI;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;
	//Изменения состояния кубов на сцене
	void changeStats(int i, int j, int type);

	UFUNCTION(BlueprintImplementableEvent)
		void CreateWidget(int Type);
protected:
	
	void SearchWinner();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Создание послеигровой статистики в BP 
	
	//Создание сетки кубов на сцене
	UFUNCTION()
		void SpawnObjects();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
