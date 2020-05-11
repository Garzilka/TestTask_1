// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses.h"
#include "NoughtsAndCrosses_AI.h"
#include "NoughtsAndCrosses_Manager.h"

// Sets default values
ANoughtsAndCrosses_Manager::ANoughtsAndCrosses_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	switch (SettingAI)
	{
	case 0:
		AI = new Easy_NoughtsAndCrosses_AI();
	default:
		AI = new Easy_NoughtsAndCrosses_AI();
	}
	
	AI->_bManager = this;
	//bPlayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController());
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Stats[i][j] = 0;
}

// Called when the game starts or when spawned
void ANoughtsAndCrosses_Manager::BeginPlay()
{
	Super::BeginPlay();
	SpawnObjects();
}





// Called every frame
void ANoughtsAndCrosses_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANoughtsAndCrosses_Manager::SpawnObjects()
{

	FActorSpawnParameters SpawnParam;
	int i = 0, j = 0;
	int a = -200, b = -200;
	FRotator B(0, 0, 0);

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{

			FVector A(b, a, 0);
			AActor* Spawn = GetWorld()->SpawnActor<AActor>(ActorToSpawn, A, B, SpawnParam);
			this->_bCubes[i][j] = Cast<ANoughtsAndCrosses>(Spawn);
			this->_bCubes[i][j]->AddActorLocalOffset(A);
			if (_bCubes[i][j] != NULL)
			{
				this->_bCubes[i][j]->horizontalPos = i;
				this->_bCubes[i][j]->verticalPos = j;
				this->_bCubes[i][j]->_bManager =  this;
			}
			a += 100;
		}
		a = -200;
		b += 100;
	}

}

void ANoughtsAndCrosses_Manager::changeStats(int i, int j, int type)
{
	Stats[i][j] = type;
	SearchWinner();
	if (type == 1)	AI->Step();
}

void ANoughtsAndCrosses_Manager::SearchWinner()
{
	int counterPlayer = 0;
	int counterAI = 0;
	bool gameOut = false;
	for (int i = 0; i < 5; i++)
	{
		for ( int j = 0; j < 5; j++)
		{
			if (Stats[i][j] == 1 || Stats[j][i] == 1)	counterPlayer++;
			if (Stats[i][j] == 2 || Stats[j][i] == 2)	counterAI++;
		}
		if (counterPlayer > 4 && !gameOut) { CreateWidget(1); gameOut = true; break; }
		if (counterAI > 4 && !gameOut)		{ CreateWidget(2); gameOut = true; break;}

		counterPlayer = 0;
		counterAI = 0;
	}
}

