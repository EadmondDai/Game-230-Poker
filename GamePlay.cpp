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
		return;
	}

	if (command == SwapCommand)
	{

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

	cout << LastChoiceDes << count << " and " << (CardsInHand - count) << endl;

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
					//tempCard = nullptr;
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



void GamePlay::InitCards()
{
	//StartCard = new Card;
	//Card *tempCard = StartCard;
	//for (int i = 0; i < CardsInHand - 1; i++)
	//{
	//	tempCard->NextCard = new Card;
	//	tempCard->NextCard->PrevieousCard = tempCard;
	//	tempCard = tempCard->NextCard;

	//	if (i == CardsInHand - 2)
	//	{
	//		EndCard = tempCard;
	//	}
	//}

	GetNewCards();
	//ShowHand();
}

void GamePlay::SetDeckManager(DeckManager obj)
{
	DeckManagerObj = obj;
}

GamePlay::GamePlay()
{
	//Prologue = "Welcome to Video Poker!";
	YourMoneyDes = "You have $";
	YoursCardDes = "Your hand contains:";
	YouPayDes = "You pay a $1 ante and now have $";
	GameOverDes = "You lost all your money. Game Over!";
	ChoiceTimeDes = "OPTIONS...\n- Type the letters for the cards you wish to keep. (i.e., ""acd"")\n- Type ""deck"" to view the cards remaining in the deck.\n- Type ""none"" to discard all cards in your hand.\n- Type ""all"" to keep all cards in your hand.\n- Type ""exit"" to exit the game.\n- Type ""swap"" to CHEAT and swap a card in your hand with one in the deck.\nYOUR CHOICE : ";
	DeckNumberDes = "Cards left in the deck: ";
	LastChoiceDes = "Here is the number of cards your kept and drew: ";

	ViewDeckCommand = "deck";
	DiscardAllCommand = "none";
	KeepAllCommand = "all";
	ExitCommand = "exit";
	SwapCommand = "swap";

	WinOnePair = "You won. You got at least one pair of jacks or higher";
	WinTwoPair = "You won. You got at least two pairs.";
	WinThreeKind = "You won. You got three of a kind";
	WinStraight = "You won. You got at least a straight";
	WinFlush = "You won. You got at least a flush";

}


GamePlay::~GamePlay()
{
}
