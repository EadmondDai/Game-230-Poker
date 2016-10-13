#include "DeckManager.h"

void DeckManager::ResetDeck(Card *FirstCard)
{
	ClearDeck();
	int count = 0;
	// If this is null, then just creat a whole new set of 
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

				if (StartCard == nullptr)
					StartCard = newCard;

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
				count++;
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
				Card *newCard = new Card;
				newCard->Number = i + 1;
				newCard->CardSuit = j;

				if (FirstCard == nullptr)
					FirstCard = newCard;

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

			}
		}

	}
	int deckCards = GetNumbersOfCard();
}

void DeckManager::ClearDeck()
{
	// Before reset, I should clear the deck before.
	while (StartCard != nullptr && StartCard->NextCard != nullptr)
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
	Card *pickedCard = StartCard;
	int targetCount = rand();
	targetCount = targetCount % (deckCards-1);
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
		StartCard = pickedCard->NextCard;
		pickedCard->NextCard->PrevieousCard = nullptr;
	}
	else
	{
		StartCard = EndCard = nullptr;
	}

	pickedCard->PrevieousCard = nullptr;
	pickedCard->NextCard = nullptr;

	return pickedCard;
}

void DeckManager::ShowDeck()
{
	// Use a temp pointer go through the pokers on player's hand.
	Card *tempShowCard = StartCard;

	while (tempShowCard != nullptr)
	{
		//printf("%n of %s , ", tempShowCard->Number, MySuitName[tempShowCard->CardSuit]);
		tempShowCard = tempShowCard->NextCard;
	}
}

DeckManager::DeckManager()
{
	// Init random with time as seed.
	srand((unsigned) time(NULL));
	ResetDeck(nullptr);
}


DeckManager::~DeckManager()
{
}
