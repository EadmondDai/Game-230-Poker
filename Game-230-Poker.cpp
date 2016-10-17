// Game-230-Poker.cpp : Defines the entry point for the console application.
//

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include "stdafx.h"
#include "GamePlay.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//{
	cout << "Welcome to Video Poker!" << endl;

	DeckManager DeckManagerObj;
	GamePlay NewGame;

	// Try to read the money from the file.
	int moneyLeft = 0;
	string line;
	ifstream myFile ("money.txt");
	if (myFile.is_open())
	{
		getline(myFile, line);
		moneyLeft = stoi(line);
		if (moneyLeft > 0)
		{
			NewGame.SetMoney(moneyLeft);
		}
		myFile.close();
	}

	cout << "You started with $" << NewGame.GetYourMoney() << endl;

	NewGame.SetDeckManager(DeckManagerObj);
	NewGame.InitCards();

	while (NewGame.IsInGame())
	{
		NewGame.BetMoney();
		NewGame.MakeAChoice();
		NewGame.GameResultCheck();
		system("pause");
	}

	DeckManagerObj.ClearDeck();
	NewGame.ClearCards();

	// Try to write the money into the file.
	// Remove the existing file first.
	remove("money.txt");
	ofstream mySaveFile;
	mySaveFile.open("money.txt");
	mySaveFile << NewGame.GetYourMoney() << endl;
	mySaveFile.close();

	//system("pause");
	//}

	//_CrtDumpMemoryLeaks();
    return 0;
}

