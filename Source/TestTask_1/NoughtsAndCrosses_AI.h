// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class ANoughtsAndCrosses_Manager;

class  ANoughtsAndCrosses_AI 
{

	
public:	
	// Sets default values for this actor's properties
	ANoughtsAndCrosses_AI();
	//UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	ANoughtsAndCrosses_Manager* _bManager;
	bool PlayerisBlockMe = false;
	int Stats[5][5];
	int line = 0;
	int colum = 0;
	bool isNeedBlockingPlayer = false;
	bool isHorizontal = true;
	void Step();
	bool checkPlayer();
	bool Horizontal_Verical();
};
