#include "DeckManager.h"

void DeckManager::ResetDeck(Card *FirstCard)
{
	ClearDeck();

	// If this is null, then just creat a whole new set of 
	if (FirstCard == nullptr)
	{
		for (int i = 0; i < NumberOfEachSuit; i++)
		{
			for (int j = Suit::Spade; j < Suit::Club; j++)
			{
				// Create the node then insert it into the deck.
				Card newCard;
				newCard.Number = i;
				newCard.CardSuit = j;

				if (FirstCard == nullptr)
					FirstCard = &newCard;

				if (EndCard == nullptr)
				{
					EndCard = &newCard;
				}
				else
				{
					EndCard->NextCard = &newCard;
					newCard.PrevieousCard = EndCard;
					EndCard = &newCard;
				}
				
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
		}

		for (int i = 0; i < NumberOfEachSuit; i++)
		{
			for (int j = Suit::Spade; j < Suit::Club; j++)
			{
				if (tempCheck.find(i * 10 + j) != tempCheck.end())
					continue;

				// Create the node then insert it into the deck.
				Card newCard;
				newCard.Number = i + 1;
				newCard.CardSuit = j;

				if (FirstCard == nullptr)
					FirstCard = &newCard;

				if (EndCard == nullptr)
				{
					EndCard = &newCard;
				}
				else
				{
					EndCard->NextCard = &newCard;
					newCard.PrevieousCard = EndCard;
					EndCard = &newCard;
				}

			}
		}

	}
}

void DeckManager::ClearDeck()
{
	// Before reset, I should clear the deck before.
	while (StartCard->NextCard != nullptr)
	{
		Card *tempPtr = StartCard->NextCard;
		delete  StartCard;
		StartCard = tempPtr;
	}
	EndCard = nullptr;
}

int DeckManager::GetNumbersOfCard()
{
	if (StartCard == nullptr)
		return 0;

	int cardCount = 1;
	Card* tempCardPtr = StartCard;
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
	int targetCount = rand();

}

DeckManager::DeckManager()
{
	// Init random with time as seed.
	srand((unsigned) time(NULL));
}


DeckManager::~DeckManager()
{
}
