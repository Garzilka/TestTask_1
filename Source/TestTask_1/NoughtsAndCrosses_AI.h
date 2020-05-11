// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class ANoughtsAndCrosses_Manager;

class NoughtsAndCrosses_AI
{
public:
	ANoughtsAndCrosses_Manager* _bManager;
	void virtual Step() = 0;
};

class  Easy_NoughtsAndCrosses_AI : public NoughtsAndCrosses_AI
{
public:	
	Easy_NoughtsAndCrosses_AI();

	bool PlayerisBlockMe = false;
	int Stats[5][5];
	int line = 0;
	int colum = 0;
	bool isNeedBlockingPlayer = false;
	bool isHorizontal = true;
	void Step() override;
	bool checkPlayer();
	bool Horizontal_Verical();
};
