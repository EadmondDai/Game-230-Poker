#pragma once
#include <set>
#include <random>
#include <time.h>

using namespace std;

enum Suit
{
	Spade,     // ??
	Heart,     // ??
	Dianmond,  // ??
	Club       // ??
};

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
	int NumberOfEachSuit;
	Card * StartCard;
	Card * EndCard;

public:
	void ResetDeck(Card *StartCard);
	void ClearDeck();
	int GetNumbersOfCard();

	Card *PickACard();


	DeckManager();
	~DeckManager();
};


void ShowCard(Card *firstCard)
{



}
