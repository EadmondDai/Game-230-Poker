#pragma once

#include <string>
#include <iostream>
#include "DeckManager.h"
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum WinReward
{
	WinOnePair = 1,
	WinTwoPair,
	WinThreeKind,
	WinStraight,
	WinFlush = 6
};

//string MySuitName[] = { "Spade" , "Heart" , "Dianmond" , "Club" };

class GamePlay
{
private:
	char StartIndex = 'a';
	int CardsInHand = 5;

	DeckManager DeckManagerObj;

	Card *StartCard = nullptr;
	Card *EndCard = nullptr;

	int YourMoney = 10;

	// GameState 0, not in game, 1 in game.
	int GameState = 1;

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

	void PickCardsFromDeck(int cardNumber);
	void DiscardUnwantedCard(); // Should not use index for this.
	
	void GetNewCards();

	bool CheckOnePair();
	bool CheckTwoPair();
	bool CheckThreeKind();
	bool CheckStraight();
	bool CheckFlush();

public:
	void SetDeckManager(DeckManager obj);
	void ShowHand();
	void BetMoney();
	void MakeAChoice();
	void GameResultCheck();
	void InitCards();

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

