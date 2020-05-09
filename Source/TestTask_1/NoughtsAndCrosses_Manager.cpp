// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses.h"

// Sets default values
ANoughtsAndCrosses_Manager::ANoughtsAndCrosses_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//ActorToSpawn = new ANoughtsAndCrosses();
}

// Called when the game starts or when spawned
void ANoughtsAndCrosses_Manager::BeginPlay()
{
	Super::BeginPlay();
	SpawnObjects();
}

void ANoughtsAndCrosses_Manager::SpawnObjects()
{
	
	FActorSpawnParameters SpawnParam;
	int i = 0,j = 0;
	int a = -200, b = -200;
	FRotator B(0, 0, 0);

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{

			FVector A(b, a, 0);
			UE_LOG(LogTemp, Log, TEXT("!Worked %f-%f"), A.X, A.Y);
			AActor* Spawn = GetWorld()->SpawnActor<AActor>(ActorToSpawn, A, B, SpawnParam);
			ANoughtsAndCrosses*t = Cast<ANoughtsAndCrosses>(Spawn);
			t->AddActorLocalOffset(A);
			if (t != NULL)
			{
				t->horizontalPos = i;
				t->verticalPos = j;

			}
			a += 100;
		}
		a = -200;
		b += 100;
	}

}

// Called every frame
void ANoughtsAndCrosses_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

