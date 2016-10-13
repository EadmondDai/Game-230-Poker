// Game-230-Poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GamePlay.h"

int main()
{
	DeckManager DeckManagerObj;
	GamePlay NewGame;
	
	NewGame.SetDeckManager(DeckManagerObj);
	NewGame.InitCards();

	while (NewGame.IsInGame())
	{
		NewGame.ShowHand();
		NewGame.MakeAChoice();
	}

	system("pause");
    return 0;
}

