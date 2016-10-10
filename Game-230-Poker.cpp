// Game-230-Poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GamePlay.h"

int main()
{
	GamePlay NewGame;
	
	while (NewGame.IsInGame())
	{
		NewGame.ShowHand();
	}

	system("pause");
    return 0;
}

