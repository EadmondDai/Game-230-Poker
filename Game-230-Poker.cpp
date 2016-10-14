// Game-230-Poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GamePlay.h"

int main()
{
	cout << "Welcome to Video Poker!" << endl;

	DeckManager DeckManagerObj;
	GamePlay NewGame;
	
	NewGame.SetDeckManager(DeckManagerObj);
	NewGame.InitCards();

	while (NewGame.IsInGame())
	{
		NewGame.BetMoney();
		NewGame.MakeAChoice();
		NewGame.GameResultCheck();
	}

	system("pause");
    return 0;
}

