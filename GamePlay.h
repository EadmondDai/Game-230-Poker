#pragma once

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

	int NumberOfEachSuit = 13;

	DeckManager DeckManagerObj;

	Card *StartCard = nullptr;
	Card *EndCard = nullptr;

	int YourMoney = 10;

	// GameState 0, not in game, 1 in game.
	int GameState = 1;

	//string Prologue;
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

	// Related to cheat
	string SelectACardToSwapDes;
	string ValueYouWantDes;
	string SuitYouWantDes;
	string InvalidInput;
	string DeckCardNotFount;

	void PickCardsFromDeck(int cardNumber);
	
	void GetNewCards();

	bool CheckOnePair();
	bool CheckTwoPair();
	bool CheckThreeKind();
	bool CheckStraight();
	bool CheckFlush();
	void CheatSwap();
	void DoSwap(Card *cardOne, Card* cardTwo);
	void SortMyCards();

public:
	void SetDeckManager(DeckManager obj);
	void ShowHand();
	void BetMoney();
	void MakeAChoice();
	void GameResultCheck();
	void InitCards();
	void ClearCards();

	void SetMoney(int money);

	bool IsInGame()
	{
		return GameState == 1;
	}

	void GameOver()
	{
		GameState = 0;
	}

	int GetYourMoney() { return YourMoney; };

	GamePlay();
	~GamePlay();
};

