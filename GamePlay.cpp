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

#include "GamePlay.h"

void GamePlay::BetMoney()
{
	YourMoney--;
	if (YourMoney < 0)
	{
		cout << GameOverDes << endl;
		GameState = 0;
		return;
	}

	cout << YouPayDes << YourMoney << endl;
	ShowHand();
}

void GamePlay::ShowHand()
{
	if (GameState == 0)
		return;

	cout << endl << YoursCardDes << endl;

	// Sort my card.
	SortMyCards();

	// Use a temp pointer go through the pokers on player's hand.
	Card *tempShowCard = StartCard;

	vector<string> cardShowName = DeckManagerObj.GetCardShowVector();

	int count = 0;
	while (tempShowCard != nullptr)
	{
		// Show the index.
		cout << (char)(StartIndex + count) << " : ";

		cout << "You got " << cardShowName[tempShowCard->Number] << " of " << MySuitName[tempShowCard->CardSuit];
		if (tempShowCard->IfKept)
		{
			cout << "(kept) ";
			tempShowCard->IfKept = false;
		}
		cout << "\n";
		tempShowCard = tempShowCard->NextCard;

		count++;
	}

	cout << endl;
}

void GamePlay::PickCardsFromDeck(int cardNumber)
{
	if (cardNumber > DeckManagerObj.GetNumbersOfCard())
	{
		DeckManagerObj.ResetDeck(StartCard);
	}

	Card *newCard = DeckManagerObj.PickACard();
	if (StartCard == nullptr)
	{
		StartCard = newCard;
		EndCard = newCard;
	}
	else
	{
		EndCard->NextCard = newCard;
		newCard->PrevieousCard = EndCard;
		EndCard = newCard;
	}
	cardNumber--;

	while (cardNumber>0)
	{
		Card *anotherCard = DeckManagerObj.PickACard();
		EndCard->NextCard = anotherCard;
		anotherCard->PrevieousCard = EndCard;
		EndCard = anotherCard;
		cardNumber--;
	}


}

void GamePlay::MakeAChoice()
{
	if (GameState == 0)
		return;

	// How many card there in the deck.
	cout << DeckNumberDes << DeckManagerObj.GetNumbersOfCard() << endl;

	cout << ChoiceTimeDes;

	string command;
	cin >> command;
	cin.clear();
	cin.ignore(1000, '\n');
	cout << endl;

	if (command == ViewDeckCommand)
	{
		DeckManagerObj.ShowDeck();
		ShowHand();
		MakeAChoice();
		return;
	}

	if (command == DiscardAllCommand)
	{
		GetNewCards();
		ShowHand();
		//GameResultCheck();
		return;
	}

	if (command == KeepAllCommand)
	{
		Card *tempCard = StartCard;
		while (tempCard != nullptr)
		{
			tempCard->IfKept = true;
			tempCard = tempCard->NextCard;
		}

		ShowHand();
		//GameResultCheck();
		return;
	}

	if (command == ExitCommand)
	{
		GameState = 0;
		DeckManager deck = DeckManagerObj;
		return;
	}

	if (command == SwapCommand)
	{
		CheatSwap();
		return;
	}


	Card *countCard = nullptr;
	// Ckeck if the input string contains index for the cards on hand.
	// My new solution is iterate through both cards and index. 
	// Change the flag of wanted cards, then discard all the left unwanted.
	int count = 0;
	for (int i = 0; i < CardsInHand; i++)
	{
		if (i == 0)
		{
			countCard = StartCard;
		}
		else
		{
			countCard = countCard->NextCard;
		}

		if (command.find(char(StartIndex + i)) != command.npos)
		{
			countCard->IfKept = true;
			count++;
		}
	}

	cout << LastChoiceDes << count << endl;

	GetNewCards();
	ShowHand();
	//GameResultCheck();
}

void GamePlay::GetNewCards()
{
	// There are two steps for getting new cards.
	// First clear the abandoned card. And sort the linked list.
	// Then get new cards form the deck.
	Card *tempCard = StartCard;
	int cardCount = 0;
	if (tempCard == nullptr)
	{
		cardCount = CardsInHand;
	}
	else
	{
		while (tempCard != nullptr)
		{
			if (tempCard->IfKept == false)
			{
				bool leftHave = tempCard->PrevieousCard != nullptr;
				bool rightHave = tempCard->NextCard != nullptr;

				if (leftHave && rightHave)
				{
					tempCard->PrevieousCard->NextCard = tempCard->NextCard;
					tempCard->NextCard->PrevieousCard = tempCard->PrevieousCard;
					Card *temp = tempCard->NextCard;
					delete tempCard;
					tempCard = temp;
				}
				else if (leftHave && !rightHave)
				{
					tempCard->PrevieousCard->NextCard = nullptr;
					EndCard = tempCard->PrevieousCard;
					delete tempCard;
					tempCard = nullptr;
				}
				else if (!leftHave && rightHave)
				{
					StartCard = tempCard->NextCard;
					tempCard = tempCard->NextCard;
					delete tempCard->PrevieousCard;
					tempCard->PrevieousCard = nullptr;
				}
				else
				{
					StartCard = EndCard = nullptr;
					delete tempCard;
					tempCard = nullptr;
				}

				cardCount++;
			}
			else
			{
				tempCard = tempCard->NextCard;
			}
		}
	}

	// Then get new card and assert in.
	PickCardsFromDeck(cardCount);

	//ShowHand();
}

void GamePlay::GameResultCheck()
{
	if (GameState == 0)
		return;
	// check if won the game.
	// check higher score first.

	// Flush $6                         // The same suit.
	// Straight $4
	// Three of a kind $3
	// Two pair $2
	// One pair, Jacks or higher $1
	// Lost

	// If I want to improve efficience, I should use one data structure to hold the infromation.
	// But that will be hard, and may have compatiable in the future for adding new function.
	bool isWinning = false;
	int moneyEarned = 0;

	if (CheckFlush())
	{
		moneyEarned += 6;
		isWinning = true;
	}
	else if (CheckStraight())
	{
		moneyEarned += 4;
		isWinning = true;
	}
	else if (CheckThreeKind())
	{
		moneyEarned += 3;
		isWinning = true;
	}
	else if (CheckTwoPair())
	{
		moneyEarned += 2;
		isWinning = true;
	}
	else if (CheckOnePair())
	{
		moneyEarned += 1;
		isWinning = true;
	}
	else 
	{

	}

	cout << endl;
	if (isWinning)
	{
		YourMoney += moneyEarned;
		cout << "You defeated" << endl;
		cout << YourMoneyDes << YourMoney << endl;
	}
	else
	{
		cout << "You died" << endl;
	}
	cout << endl;

	GetNewCards();
}

bool GamePlay::CheckFlush()
{
	Card *tempCard = StartCard;
	while (tempCard->NextCard != nullptr)
	{
		if (tempCard->CardSuit != tempCard->NextCard->CardSuit)
		{
			return false;
		}
		tempCard = tempCard->NextCard;
	}
	return true;
}

bool GamePlay::CheckStraight()
{
	vector<int> checkVector;
	Card *tempCard = StartCard;
	while (tempCard != nullptr)
	{
		checkVector.push_back(tempCard->Number);
		tempCard = tempCard->NextCard;
	}
	sort(checkVector.begin(), checkVector.end());
	for (int i = 0; i < checkVector.size() - 1; i++)
	{
		if (checkVector[i] != checkVector[i + 1] - 1)
			return false;
	}

	return true;
}

bool GamePlay::CheckThreeKind()
{
	// To check this.
	// I will need a array to count numbers of suit encountered.
	map<int, int> checkMap;
	Card *tempCard = StartCard;
	while (tempCard != nullptr)
	{
		int number = tempCard->Number;
		if (checkMap.find(number) == checkMap.end())
		{
			checkMap[number] = 1;
		}
		else
		{
			checkMap[number] = checkMap[number] + 1;
			if (checkMap[number] >= 3)
				return true;
		}
		tempCard = tempCard->NextCard;
	}

	return false;
}

bool GamePlay::CheckTwoPair()
{
	map<int, int> checkMap;
	Card *tempCard = StartCard;
	while (tempCard!= nullptr)
	{
		int number = tempCard->Number;
		if (checkMap.find(number) == checkMap.end())
		{
			checkMap[number] = 1;
		}
		else
		{
			checkMap[number] = checkMap[number] + 1;
		}
		tempCard = tempCard->NextCard;
	}

	int count = 0;
	for (map<int, int>::iterator it = checkMap.begin(); it != checkMap.end();it++)
	{
		if (it->second >= 2)
		{
			count++;
		}
	}

	if (count >= 2)
	{
		return true;
	}

	return false;
}

bool GamePlay::CheckOnePair()
{
	map<int, int> checkMap;
	Card *tempCard = StartCard;
	while (tempCard != nullptr)
	{
		int number = tempCard->Number;
		if (checkMap.find(number) == checkMap.end())
		{
			checkMap[number] = 1;
		}
		else
		{
			return true;
		}
		tempCard = tempCard->NextCard;
	}

	return false;
}

void GamePlay::ClearCards()
{
	if (StartCard == nullptr)
		return;

	Card *tempCard = StartCard;

	int count = 0;
	while (StartCard != nullptr)
	{
		//if (returnCard->IfKept == false)
		//{
		//bool previeousHaveCard = tempCard->PrevieousCard != nullptr;
		//bool nextHaveCard = tempCard->NextCard != nullptr;

		//if (previeousHaveCard && nextHaveCard)
		//{
		//	tempCard->PrevieousCard->NextCard = tempCard->NextCard;
		//	tempCard->NextCard->PrevieousCard = tempCard->PrevieousCard;
		//	Card *temp = tempCard;
		//	tempCard = tempCard->NextCard;
		//	delete temp;
		//}
		//else if (previeousHaveCard && !nextHaveCard)
		//{
		//	tempCard->PrevieousCard->NextCard = nullptr;
		//	delete tempCard;
		//	tempCard = nullptr;
		//}
		//else if (!previeousHaveCard && nextHaveCard)
		//{
		//	tempCard = tempCard->NextCard;
		//	delete tempCard->PrevieousCard;
		//	tempCard->PrevieousCard = nullptr;
		//}
		//else
		//{
		//	delete tempCard;
		//	tempCard = nullptr;
		//}
		//}
		
		tempCard = StartCard->NextCard;
		delete StartCard;
		StartCard = tempCard;
		count++;
	}
	cout << count;
}

void GamePlay::CheatSwap()
{
	Card *myCard = nullptr;
	Card *deckCard = nullptr;
	int deckCardNum;
	int deckCardSuit;

	while (true)
	{
		cout << SelectACardToSwapDes << endl;
		string SelectCardStr;
	
		cin >> SelectCardStr;
		cin.clear();
		cin.ignore(1000, '\n');

		if (SelectCardStr == ExitCommand)
		{
			GameState = 0;
			return;
		}

		if (SelectCardStr[0] < 'a' || SelectCardStr[0] > 'e')
		{
			cout << InvalidInput << endl;
			ShowHand();
			MakeAChoice();
			return;
		}
		else
		{
			int count = StartIndex + CardsInHand - SelectCardStr[0];
			Card *temp = StartCard;
			count--;
			while (count > 0)
			{
				temp = temp->NextCard;
				count--;
			}
			myCard = temp;
			break;
		}
	}

	while (true)
	{
		cout << ValueYouWantDes << endl;

		string SelectNumStr;
		cin >> SelectNumStr;
		cin.clear();
		cin.ignore(1000, '\n');

		if (SelectNumStr == ExitCommand)
		{
			GameState = 0;
			return;
		}

		int inputNum = stoi(SelectNumStr);
		if (inputNum <= 0 || inputNum > NumberOfEachSuit)
		{
			cout << InvalidInput << endl;
			ShowHand();
			MakeAChoice();
			return;
		}
		else
		{
			deckCardNum = inputNum;
			break;
		}

	}

	while (true)
	{
		cout << SuitYouWantDes << endl;

		string SelectSuitStr;
		cin >> SelectSuitStr;
		cin.clear();
		cin.ignore(1000, '\n');

		if (SelectSuitStr == ExitCommand)
		{
			GameState = 0;
			return;
		}

		int inputSuit = stoi(SelectSuitStr);
		if (inputSuit < Suit::Club || inputSuit > Suit::Spade)
		{
			cout << InvalidInput << endl;
			ShowHand();
			MakeAChoice();
			return;
		}
		else
		{
			deckCardSuit = inputSuit;
			break;
		}
	}

	deckCard = DeckManagerObj.PickACardWithNumAndSuit(deckCardNum - 1, deckCardSuit);
	if (deckCard == nullptr)
	{
		cout << DeckCardNotFount << endl;
	}
	else
	{
		DoSwap(myCard, deckCard);
	}
	ShowHand();
	MakeAChoice();
	return;
}

void GamePlay::DoSwap(Card* cardOne, Card* cardTwo)
{
	// Make a copy of the changing card first.
	Card* temp = new Card;
	temp->Number = cardOne->Number;
	temp->CardSuit = cardOne->CardSuit;
	temp->PrevieousCard = cardOne->PrevieousCard;
	temp->NextCard = cardOne->NextCard;
	

	// Move cardOne to cardTwo.
	if (cardTwo->PrevieousCard != nullptr)
	{
		cardTwo->PrevieousCard->NextCard = cardOne;
		cardOne->PrevieousCard = cardTwo->PrevieousCard;
	}
	else
	{
		cardOne->PrevieousCard = nullptr;
	}

	if (cardTwo->NextCard != nullptr)
	{
		cardTwo->NextCard->PrevieousCard = cardOne;
		cardOne->NextCard = cardTwo->NextCard;
	}
	else
	{
		cardOne->NextCard = nullptr;
	}

	// Then move cardTwo to cardOne.
	if (temp->PrevieousCard != nullptr)
	{
		temp->PrevieousCard->NextCard = cardTwo;
		cardTwo->PrevieousCard = temp->PrevieousCard;
	}
	else
	{
		cardTwo->PrevieousCard = nullptr;
	}

	if (temp->NextCard != nullptr)
	{
		temp->NextCard->PrevieousCard = cardTwo;
		cardTwo->NextCard = temp->NextCard;
	}
	else
	{
		cardTwo->NextCard = nullptr;
	}
	delete temp;
}

void GamePlay::InitCards()
{
	GetNewCards();
}

void GamePlay::SetDeckManager(DeckManager obj)
{
	DeckManagerObj = obj;
}

void GamePlay::SortMyCards()
{
	// Using Bubble up method for this.
	// Basic idea is use another pointer pointed to the card. Then try to find the suitable position before itself and inserted it in.

	// StartCard is considered already sorted.
	Card *toBeSortCard = StartCard->NextCard;
	Card *nextSortCard = toBeSortCard->NextCard;

	while (toBeSortCard != nullptr)
	{
		// Then find a node before nextSortCard that is suitabel for insertion.
		Card *posiFindCard = toBeSortCard->PrevieousCard;

		// Cut the toBeSortCard out first.
		toBeSortCard->PrevieousCard->NextCard = toBeSortCard->NextCard;
		if(toBeSortCard->NextCard != nullptr)
			toBeSortCard->NextCard->PrevieousCard = toBeSortCard->PrevieousCard;
		toBeSortCard->PrevieousCard = nullptr;
		toBeSortCard->NextCard = nullptr;

		while (posiFindCard != nullptr)
		{
			// Compare the value and suit for the two card.
			// If found the card value is lower than mind, inerst behind it.
			if ((toBeSortCard->Number + 1 ) * 10 + toBeSortCard->CardSuit >= (posiFindCard->Number + 1) * 10 + posiFindCard->CardSuit)
			{
				// Get the toBeSortedCard in front of posiFindCard
				toBeSortCard->PrevieousCard = posiFindCard;
				toBeSortCard->NextCard = posiFindCard->NextCard;
				
				if (posiFindCard->NextCard != nullptr)
				{
					posiFindCard->NextCard->PrevieousCard = toBeSortCard;
				}
				posiFindCard->NextCard = toBeSortCard;
				break;
			}
			else if (posiFindCard->PrevieousCard == nullptr)
			{
				toBeSortCard->NextCard = posiFindCard;
				posiFindCard->PrevieousCard = toBeSortCard;
				StartCard = toBeSortCard;
				break;
			}
			posiFindCard = posiFindCard->PrevieousCard;
		}

		toBeSortCard = nextSortCard;
		if(nextSortCard != nullptr)
			nextSortCard = nextSortCard->NextCard;
	}

	Card *tempEndCardFinder = StartCard;

	while (tempEndCardFinder->NextCard != nullptr)
	{
		tempEndCardFinder = tempEndCardFinder->NextCard;
	}
	EndCard = tempEndCardFinder;
}

GamePlay::GamePlay()
{
	//Prologue = "Welcome to Video Poker!";
	YourMoneyDes = "You have $";
	YoursCardDes = "Your hand contains:";
	YouPayDes = "You pay a $1 ante and now have $";
	GameOverDes = "You lost all your money. Game Over!";
	ChoiceTimeDes = "OPTIONS...\n- Type the letters for the cards you wish to keep. (i.e., ""acd"")\n- Type ""deck"" to view the cards remaining in the deck.\n- Type ""none"" to discard all cards in your hand.\n- Type ""all"" to keep all cards in your hand.\n- Type ""exit"" to exit the game.\n- Type ""swap"" to CHEAT and swap a card in your hand with one in the deck.\nYou can only choose a card from your deck to swap with one in the deck.\n YOUR CHOICE : ";
	DeckNumberDes = "Cards left in the deck: ";
	LastChoiceDes = "Here is the number of cards your kept: ";

	ViewDeckCommand = "deck";
	DiscardAllCommand = "none";
	KeepAllCommand = "all";
	ExitCommand = "exit";
	SwapCommand = "swap";

	SelectACardToSwapDes = "Use a index like 'a' to choose a card. Accept only one card no matter how many you input. Input other staff wouldn't be accepted.";
	ValueYouWantDes = "Chose a value you want from the deck. Better be the one deck contains( 1 - 13). Input value not showing in the deck is invalid.";
	SuitYouWantDes = "Chose a suit you want through input a number. 0 for Club, 1 for Diamond, 2 for Heart, 3 for Spade. Other input wouldn't be accepted.";
	InvalidInput = "Invalid input. See, even if you want to cheat, you still need to follow certain rules.";
	DeckCardNotFount = "404 not found. Not sure what happened, but the card you want in the deck, is just a illusion, never existed.";

	WinOnePair = "You won. You got at least one pair of jacks or higher";
	WinTwoPair = "You won. You got at least two pairs.";
	WinThreeKind = "You won. You got three of a kind";
	WinStraight = "You won. You got at least a straight";
	WinFlush = "You won. You got at least a flush";

}


GamePlay::~GamePlay()
{
}
