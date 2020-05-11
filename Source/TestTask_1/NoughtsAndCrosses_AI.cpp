// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses_AI.h"
#include "NoughtsAndCrosses_Manager.h"

// Sets default values
ANoughtsAndCrosses_AI::ANoughtsAndCrosses_AI()
{
	
}

void ANoughtsAndCrosses_AI::Step()
{
	int counter = 0;
	bool can = true;
	int line = 0;
	int colum = 0;
	int Counter = 0;
	bool isHorizontal = true;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			isHorizontal = true;
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] != 1)
			{
				Counter++;
			}
			if (Counter > 4)
			{
				line = i;
				colum = j;
				break;
			}
		}
		if (Counter == 5) break;
		Counter = 0;
			isHorizontal = false;			
	}
	if (isHorizontal)
	{	
		UE_LOG(LogTemp, Log, TEXT("Tactic Horizontal"));	

	for (int i = line; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 0 && can)
			{
				UE_LOG(LogTemp, Log, TEXT("Select [%d,%d]"), i, j);
				Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[i][j]->Enabled(false);
				return;
			}
			can = true;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				isHorizontal = true;
				if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[j][i] != 1)
				{
					Counter++;
				}
				if (Counter > 4)
				{
					line = i;
					colum = j;
					break;
				}
			}
			if (Counter == 5) break;
			Counter = 0;
		}
		UE_LOG(LogTemp, Log, TEXT("Tactic Vertical"));
		for (int i = line; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[j][i] == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("Select [%d,%d]"), j, i);
					Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[j][i]->Enabled(false);
					return;
				}
				can = true;
			}
	}
}
	/*for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Stats[i][j] = Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (Stats[i][j] != 1)
				counter++;
			if (counter > 4)
				for (int j1 = 0; j1 < 5; j1++)
					if (Stats[i][j1] != 2)
					{
						Stats[i][j1] = 2;
						Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[i][j]->Enabled(false);
					}
		}*/




