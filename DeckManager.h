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
	Spade,     // ??
	Heart,     // ??
	Dianmond,  // ??
	Club       // ??
};

// Make this global
static string MySuitName[] = { "Spade" , "Heart" , "Dianmond" , "Club" };

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
	Card * StartCard = nullptr;
	Card * EndCard = nullptr;

	void DiscardUnwantedCard();

public:
	void ResetDeck(Card *StartCard);
	void ClearDeck();
	void ShowDeck();
	
	int GetNumbersOfCard();

	Card *GetStartCard() { return StartCard; };

	Card *PickACard();

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
