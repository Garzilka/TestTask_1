// Fill out your copyright notice in the Description page of Project Settings.


#include "NoughtsAndCrosses_AI.h"
#include "NoughtsAndCrosses_Manager.h"

// Sets default values
Easy_NoughtsAndCrosses_AI::Easy_NoughtsAndCrosses_AI()
{
	
}

void Easy_NoughtsAndCrosses_AI::Step()
{
	bool can = true;

	if (!checkPlayer())
	{
		if (Horizontal_Verical())
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					//Проверка линии
					for (int j1 = 0; j1 < 5; j1++)
						if (_bManager->Stats[i][j1] == 1)
						{
							j = 5;
							can = false;
						}					
					if (_bManager->Stats[i][j] == 0 && can)
					{
						_bManager->_bCubes[i][j]->Enabled(false);
						return;
					}
					
				}
				can = true;
			}
		
		else
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					for (int j1 = 0; j1 < 5; j1++)
					{
						if (_bManager->Stats[j1][i] == 1)
						{
							j = 5;
							can = false;
						}
					}
					if (_bManager->Stats[j][i] == 0 && can)
					{
						_bManager->_bCubes[j][i]->Enabled(false);
						return;	
					}
				}
				can = true;
			}
		}
		UE_LOG(LogTemp, Log, TEXT("There are no winning tactics"));
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (_bManager->Stats[i][j] == 0)
				{
					_bManager->_bCubes[i][j]->Enabled(false);
					_bManager->CreateWidget(0);
					return;
				}
	}
}
bool Easy_NoughtsAndCrosses_AI::checkPlayer()
{
	int counterPlayer = 0;
	isNeedBlockingPlayer = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_bManager->Stats[i][j] == 1)
			{
				counterPlayer++;
			}
			if (_bManager->Stats[i][j] == 2)
			{
				counterPlayer = 0; break;
			}
			if (counterPlayer > 3)
			{
				for (int j1 = 0; j1 < 5; j1++)				
					if (_bManager->Stats[i][j1] == 0)
					{
						_bManager->_bCubes[i][j1]->Enabled(false);
						isNeedBlockingPlayer = true;
						return true;
					}
				break;
			}
		}
		if (counterPlayer > 3)	break;
		counterPlayer = 0;
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (_bManager->Stats[i][j] == 1)
			{
				counterPlayer++;
			}
			if (counterPlayer > 3)
			{
				for (int i1 = 0; i1 < 5; i1++)
				{
					if (_bManager->Stats[i1][j] == 0)
					{
						UE_LOG(LogTemp, Log, TEXT("Can block [%d,%d]"), i1, j);
						_bManager->_bCubes[i1][j]->Enabled(false);
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

bool Easy_NoughtsAndCrosses_AI::Horizontal_Verical()
{
	int Counter = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			if (_bManager->Stats[i][j] == 1)
			{
				j = 5;
				Counter++;
			}
		if (Counter > 4)
			return false;
	}
	return true;
}



