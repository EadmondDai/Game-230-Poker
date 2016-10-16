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

#pragma once
#include <set>
#include <random>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

// Suit name;
static enum Suit
{
	Club,
	Diamond,
	Heart,
	Spade
};

// Make this global
static string MySuitName[] = {"Club", "Diamond", "Heart" , "Spade"};

struct Card
{
	int Number;
	int CardSuit;
	Card *PrevieousCard = nullptr;
	Card *NextCard = nullptr;
	bool IfKept = false;
};


class DeckManager
{

private:
	int WarpNumber = 6;
	int NumberOfEachSuit = 13;
	Card * DeckFirstCard = nullptr;
	Card * EndCard = nullptr;

public:
	void ResetDeck(Card *DeckFirstCard);
	void ClearDeck();
	void ShowDeck();
	
	int GetNumbersOfCard();

	Card *GetStartCard() { return DeckFirstCard; };

	Card *PickACard();

	// Relation with each others remains in the returen card.
	Card *PickACardWithNumAndSuit(int num, int suit);

	// Card Showing Name
	vector<string> CardShowVector;

	vector<string> GetCardShowVector();

	DeckManager();
	~DeckManager();
};


// These function I should really put them in a separate file.

//void DiscardCards(Card *firstCard)
//{
//	while (firstCard->NextCard != nullptr)
//	{
//		firstCard = firstCard->NextCard;
//		delete firstCard->PrevieousCard;
//		//firstCard->PrevieousCard = nullptr;  In fact, do not need this line;
//	}
//	delete firstCard;
//}
