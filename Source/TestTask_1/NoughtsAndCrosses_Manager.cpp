// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses.h"
#include "NoughtsAndCrosses_AI.h"
#include "NoughtsAndCrosses_Manager.h"

// Sets default values
ANoughtsAndCrosses_Manager::ANoughtsAndCrosses_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AI = new ANoughtsAndCrosses_AI();
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
	if (type == 1)
	{
		AI->Step();
	}
}

void ANoughtsAndCrosses_Manager::SearchWinner()
{
	int counterC = 0;
	int counterZ = 0;
	int currentType = Stats[0][0];
	int i = 0, j = 0;
	
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (Stats[i][j] == 1)
				counterC++;
			else if (Stats[i][j] == 2) counterC = 0;

			if (Stats[i][j] == 2)
				counterZ++;
			else if (Stats[i][j] == 1) counterZ = 0;
		}
		if (counterC > 4)
			UE_LOG(LogTemp, Log, TEXT("Line : %d Count cross   %d, Count zero %d"), i, counterC, counterZ);
		if (counterC == 5)
			UE_LOG(LogTemp, Log, TEXT("Player Win!!!"));
		if (counterZ == 5)
			UE_LOG(LogTemp, Log, TEXT("AI Win!!!"));
		counterC = 0;
		counterZ = 0;
	}
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (Stats[j][i] == 1)
				counterC++;
			else if (Stats[j][i] == 2) counterC = 0;

			if (Stats[j][i] == 2)
				counterZ++;
			else if (Stats[j][i] == 1) counterZ = 0;
		}
		if (counterC > 3)
			UE_LOG(LogTemp, Log, TEXT("Line : %d Count cross   %d, Count zero %d"), j, counterC, counterZ);
		if (counterC == 5 || counterZ == 5)
			UE_LOG(LogTemp, Log, TEXT("Win!!!"));
		counterC = 0;
		counterZ = 0;
	}
	

	
}
