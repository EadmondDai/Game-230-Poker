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

string SuitName[] = { "Spade" , "Heart" , "Dianmond" , "Club" };

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
	void ShowDeck();
	
	int GetNumbersOfCard();

	Card *GetStartCard() { return StartCard; };

	Card *PickACard();


	DeckManager();
	~DeckManager();
};


// These function I should really put them in a separate file.

void DiscardCards(Card *firstCard)
{
	while (firstCard->NextCard != nullptr)
	{
		firstCard = firstCard->NextCard;
		delete firstCard->PrevieousCard;
		//firstCard->PrevieousCard = nullptr;  In fact, do not need this line;
	}
	delete firstCard;
}
