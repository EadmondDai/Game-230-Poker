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


#include "DeckManager.h"

void DeckManager::ResetDeck(Card *FirstCard)
{
	ClearDeck();
	//DiscardUnwantedCard();

	// If this is null, then just creat a whole new set of 
	int resetOne = 0;
	int resetTwo = 0;
	if (FirstCard == nullptr)
	{
		for (int i = 0; i < NumberOfEachSuit; i++)
		{
			for (int j = Suit::Spade; j <= Suit::Club; j++)
			{
				// Create the node then insert it into the deck.
				Card *newCard = new Card;
				newCard->Number = i;
				newCard->CardSuit = j;

				if (DeckFirstCard == nullptr)
					DeckFirstCard = newCard;

				if (EndCard == nullptr)
				{
					EndCard = newCard;
				}
				else
				{
					EndCard->NextCard = newCard;
					newCard->PrevieousCard = EndCard;
					EndCard = newCard;
				}
				resetOne++;
			}
		}
	}
	else
	{
		// If iterate through the list passed in everything before I try to create a new node, could be costy on performance.
		// I could use other method to improve efficience.
		// Use set, map or dictionary could be the best way.
		set<int> tempCheck;
		Card *tempCard = FirstCard;
		while (tempCard != nullptr)
		{
			tempCheck.insert(tempCard->Number * 10 + tempCard->CardSuit);
			tempCard = tempCard->NextCard;
		}

		for (int i = 0; i < NumberOfEachSuit; i++)
		{
			for (int j = Suit::Spade; j <= Suit::Club; j++)
			{
				if (tempCheck.find(i * 10 + j) != tempCheck.end())
					continue;

				// Create the node then insert it into the deck.
				Card *newCard = new Card;
				newCard->Number = i;
				newCard->CardSuit = j;

				if (DeckFirstCard == nullptr)
					DeckFirstCard = newCard;

				if (EndCard == nullptr)
				{
					EndCard = newCard;
				}
				else
				{
					EndCard->NextCard = newCard;
					newCard->PrevieousCard = EndCard;
					EndCard = newCard;
				}
				resetTwo++;
			}
		}
	}

	cout << resetOne << resetTwo;
}

void DeckManager::ClearDeck()
{
	// Before reset, I should clear the deck before.
	int count = 0;
	while (DeckFirstCard != nullptr)
	{
		Card *tempPtr = DeckFirstCard;
		DeckFirstCard = DeckFirstCard->NextCard;
		delete tempPtr;
		count++;
	}
	EndCard = nullptr;
}

int DeckManager::GetNumbersOfCard()
{
	if (DeckFirstCard == nullptr)
		return 0;

	int cardCount = 1;
	Card* tempCardPtr = DeckFirstCard;
	while (tempCardPtr -> NextCard != nullptr)
	{
		cardCount++;
		tempCardPtr = tempCardPtr->NextCard;
	}
	return cardCount;
}   

Card *DeckManager::PickACard()
{
	int deckCards = GetNumbersOfCard();
	Card *pickedCard = DeckFirstCard;
	int targetCount = rand();
	targetCount = (targetCount % deckCards);
	while (targetCount > 0 )
	{
		pickedCard = pickedCard->NextCard;
		targetCount--;
	}
	
	bool leftHave = pickedCard->PrevieousCard != nullptr;
	bool rightHave = pickedCard->NextCard != nullptr;

	if (leftHave && rightHave)
	{
		pickedCard->PrevieousCard->NextCard = pickedCard->NextCard;
		pickedCard->NextCard->PrevieousCard = pickedCard->PrevieousCard;
	}
	else if (leftHave && !rightHave)
	{
		pickedCard->PrevieousCard->NextCard = nullptr;
		EndCard = pickedCard->PrevieousCard;
	}
	else if (!leftHave && rightHave)
	{
		DeckFirstCard = pickedCard->NextCard;
		pickedCard->NextCard->PrevieousCard = nullptr;
	}
	else
	{
		DeckFirstCard = EndCard = nullptr;
	}

	pickedCard->PrevieousCard = nullptr;
	pickedCard->NextCard = nullptr;

	return pickedCard;
}

Card *DeckManager::PickACardWithNumAndSuit(int num, int suit)
{
	Card *returnCard = DeckFirstCard;
	while (returnCard != nullptr )
	{
		if (returnCard->Number == num && returnCard->CardSuit == suit)
		{
			return returnCard;
		}
		else
		{
			returnCard = returnCard->NextCard;
		}
	}
	return returnCard;
}

void DeckManager::ShowDeck()
{
	// Use a temp pointer go through the pokers on player's hand.
	Card *tempShowCard = DeckFirstCard;

	int warpCount = WarpNumber;
	while (tempShowCard != nullptr)
	{
		//printf("%n of %s , ", tempShowCard->Number, MySuitName[tempShowCard->CardSuit]);
		cout << CardShowVector[tempShowCard->Number] << " of " << MySuitName[tempShowCard->CardSuit];
		if (tempShowCard->NextCard != nullptr)
		{
			cout << " , ";
		}
		else
		{
			cout << endl;
		}
		tempShowCard = tempShowCard->NextCard;

		warpCount--;
		if (warpCount < 0)
		{
			cout << endl;
			warpCount = WarpNumber;
		}
	}
}

vector<string> DeckManager::GetCardShowVector()
{
	return CardShowVector;
}

DeckManager::DeckManager()
{
	// Init random with time as seed.
	srand((unsigned) time(NULL));
	//ResetDeck(nullptr);

	CardShowVector.push_back("Ace");
	for (int i = 2; i <= 10; i++)
	{
		CardShowVector.push_back(to_string(i));
	}
	CardShowVector.push_back("Jack");
	CardShowVector.push_back("Queen");
	CardShowVector.push_back("King");
}


DeckManager::~DeckManager()
{
}
