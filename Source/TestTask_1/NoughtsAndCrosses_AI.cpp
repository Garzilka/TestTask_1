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
	int Counter = 0;
	bool can = true;
	if (!checkPlayer())
	{
		if (Horizontal_Verical())
		{
			UE_LOG(LogTemp, Log, TEXT("Tactic Horizontal"));

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					for (int j1 = 0; j1 < 5; j1++)
					{
						if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j1] == 1)
						{
							j = 5;
							can = false;
						}
					}
					if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 0 && can)
					{
						UE_LOG(LogTemp, Log, TEXT("Select [%d,%d]"), i, j);
						Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[i][j]->Enabled(false);
						return;
					}
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
			for (int i = 0; i < 5; i++)
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
}
bool ANoughtsAndCrosses_AI::checkPlayer()
{
	int counterPlayer = 0;
	isHorizontal = true;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 1)
			{
				counterPlayer++;
			}
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 2)
			{
				counterPlayer = 0; break;
			}
			if (counterPlayer > 3)
			{
				for (int j1 = 0; j1 < 5; j1++)				
					if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j1] == 0)
					{
						UE_LOG(LogTemp, Log, TEXT("Can block [%d,%d]"), i, j1);
						Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[i][j1]->Enabled(false);
						isNeedBlockingPlayer = true;
						return true;
					}
				break;
			}
		}
		if (counterPlayer > 3)
		{
			break;
		}
		counterPlayer = 0;
	}
	if(!isNeedBlockingPlayer)
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 1)
			{
				counterPlayer++;
			}
			if (counterPlayer > 3)
			{
				for (int i1 = 0; i1 < 5; i1++)
				{
					if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i1][j] == 0)
					{
						UE_LOG(LogTemp, Log, TEXT("Can block [%d,%d]"), i1, j);
						Cast<ANoughtsAndCrosses_Manager>(_bManager)->_bCubes[i1][j]->Enabled(false);
						return true;
						break;
					}
				}
				break;
			}
		}
		if (counterPlayer > 3)
		{
			break;
		}
		counterPlayer = 0;
	}
	return false;
}

bool ANoughtsAndCrosses_AI::Horizontal_Verical()
{
	int Counter = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (Cast<ANoughtsAndCrosses_Manager>(_bManager)->Stats[i][j] == 1)
			{
				j = 5;
				Counter++;
			}
	if (Counter > 4)
		return false;
	return true;
}



