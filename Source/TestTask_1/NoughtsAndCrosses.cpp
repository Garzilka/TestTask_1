// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses.h"

// Sets default values
ANoughtsAndCrosses::ANoughtsAndCrosses()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mMyMesh_"));
	mMesh->SetupAttachment(RootComponent);

	_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	_Box->SetupAttachment(mMesh);
	
	OffMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OffMaterial"));
	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));

	Place = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pPlace"));
	MeshCross = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mMeshCross_"));
	MeshZero = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mMeshZero_"));
	Place->SetupAttachment(_Box);
	MeshCross->SetupAttachment(Place);
	MeshZero->SetupAttachment(Place);




	
	
	
}

void ANoughtsAndCrosses::Enabled(bool Type)
{
	if (Type)
	{
		Place->SetStaticMesh(MeshCross->GetStaticMesh());
		if (_bManager != NULL)
			Cast<ANoughtsAndCrosses_Manager>(_bManager)->changeStats(verticalPos, horizontalPos, 1);
		
	}
	else
	{
		Place->SetStaticMesh(MeshZero->GetStaticMesh());
		if (_bManager != NULL)
			Cast<ANoughtsAndCrosses_Manager>(_bManager)->changeStats(verticalPos, horizontalPos, 2);
		
	}

	
}


// Called when the game starts or when spawned
void ANoughtsAndCrosses::BeginPlay()
{
	Super::BeginPlay();
	mMesh->SetMaterial(0, OffMaterial);
}

// Called every frame
void ANoughtsAndCrosses::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isSelect)
	{
		if(GetActorLocation().Z<=60)
			this->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z + 1.f));
		if(OnMaterial!= NULL)
			mMesh->SetMaterial(0, OnMaterial);
	}
	else if (GetActorLocation().Z > 0)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 0.5f));
		
		if (OffMaterial != NULL)
			mMesh->SetMaterial(0, OffMaterial);
	}
	isSelect = false;

}

