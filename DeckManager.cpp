#include "DeckManager.h"

void DeckManager::ResetDeck(Card *FirstCard)
{
	ClearDeck();
	int count = 0;

	//DiscardUnwantedCard();

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

			}
		}
	}
}


void DeckManager::DiscardUnwantedCard()
{
	if (StartCard == nullptr)
		return;

	Card *tempCard = StartCard;

	while (tempCard != nullptr)
	{
		//if (returnCard->IfKept == false)
		//{
			bool previeousHaveCard = tempCard->PrevieousCard != nullptr;
			bool nextHaveCard = tempCard->NextCard != nullptr;

			if (previeousHaveCard && nextHaveCard)
			{
				tempCard->PrevieousCard->NextCard = tempCard->NextCard;
				tempCard->NextCard->PrevieousCard = tempCard->PrevieousCard;
				Card *temp = tempCard;
				tempCard = tempCard->NextCard;
				delete temp;
			}
			else if (previeousHaveCard && !nextHaveCard)
			{
				tempCard->PrevieousCard->NextCard = nullptr;
				delete tempCard;
				tempCard = nullptr;
			}
			else if (!previeousHaveCard && nextHaveCard)
			{
				tempCard = tempCard->NextCard;
				delete tempCard->PrevieousCard;
				tempCard->PrevieousCard = nullptr;
			}
			else
			{
				delete tempCard;
				tempCard = nullptr;
			}
		//}
	}
}

void DeckManager::ClearDeck()
{
	// Before reset, I should clear the deck before.
	while (StartCard != nullptr)
	{
		Card *tempPtr = StartCard;
		StartCard = StartCard->NextCard;
		delete tempPtr;
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
	targetCount = (targetCount % deckCards) - 1;
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
	ResetDeck(nullptr);

	CardShowVector.push_back("Ace");
	for (int i = 1; i < 10; i++)
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
