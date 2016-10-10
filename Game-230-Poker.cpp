// Game-230-Poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GamePlay.h"

int main()
{
	GamePlay NewGame;
	DeckManager DeckManagerObj;
	NewGame.SetDeckManager(DeckManagerObj);

	while (NewGame.IsInGame())
	{
		NewGame.ShowHand();
		NewGame.MakeAChoice();
	}

	system("pause");
    return 0;
}

