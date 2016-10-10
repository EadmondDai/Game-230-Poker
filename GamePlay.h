#pragma once

#include <string>
#include <iostream>
#include "DeckManager.h"

using namespace std;

enum WinReward
{
	WinOnePair = 1,
	WinTwoPair,
	WinThreeKind,
	WinStraight,
	WinFlush = 6
};

class GamePlay
{
private:
	int YourMoney;

	// GameState 0, not in game, 1 in game.
	int GameState = 1;

	Card *StartCard = nullptr;

	string Prologue;
	string YoursCardDes;
	string YourMoneyDes;
	string YouPayDes;
	string GameOverDes;
	string ChoiceTimeDes;
	string DeckNumberDes;
	string LastChoiceDes;

	string ViewDeckCommand;
	string DiscardAllCommand;
	string KeepAllCommand;
	string ExitCommand;
	string SwapCommand;

	string WinOnePair;
	string WinTwoPair;
	string WinThreeKind;
	string WinStraight;
	string WinFlush;

	void PickACard();
	
	bool CheckOnePair();
	bool CheckTwoPair();
	bool CheckThreeKind();
	bool CheckStraight();
	bool CheckFlush();

public:
	void ShowHand();

	bool IsInGame()
	{
		return GameState == 1;
	}

	void GameOver()
	{
		GameState = 0;
	}

	GamePlay();
	~GamePlay();
};

