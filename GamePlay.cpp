#include "GamePlay.h"

void GamePlay::ShowHand()
{

	cout << YoursCardDes << endl;

	// Use a temp pointer go through the pokers on player's hand.
	Card *tempShowCard = StartCard;

	while (tempShowCard != nullptr)
	{
		cout << "You got " << tempShowCard->Number << "of" << SuitName[tempShowCard->CardSuit];
		if (tempShowCard->IfKept)
		{
			cout << "(kept)";
			tempShowCard->IfKept = false;
		}
		cout << endl;
		tempShowCard = tempShowCard->NextCard;
	}

	

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
	cout << ChoiceTimeDes << endl;

	string command;
	cin >> command;
	cin.clear();
	cin.ignore(1000, '\n');

	if (command == ViewDeckCommand)
	{
		ShowCard(DeckManagerObj.GetStartCard());
		MakeAChoice();
		return;
	}

	if (command == DiscardAllCommand)
	{

		DiscardCards(StartCard);
		StartCard = nullptr;
		EndCard = nullptr;
		GameResult();
		return;
	}

	if (command == KeepAllCommand)
	{
		GameResult();
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


	Card *newStartCard = nullptr;
	Card *newEndCard = nullptr;
	// Ckeck if the input string contains index for the cards on hand.
	for (int i = 0; i < CardsInHand; i++)
	{
		if (command.find(char(StartIndex + i)))
		{
			Card *newCard = PickACardFromHand(i);
		}
	}

}


void GamePlay::GameResult()
{

}

Card *GamePlay::PickACardFromHand(int index)
{
	if (index >= CardsInHand)
	{
		cout << "You do not have that many cards." << endl;
		return;
	}

	Card *returnCard = nullptr;
	returnCard = StartCard;
	index--;
	while (index >= 0)
	{
		returnCard = returnCard->NextCard;
		index--;
	}

	bool previeousHaveCard = returnCard->PrevieousCard != nullptr;
	bool nextHaveCard = returnCard->NextCard != nullptr;
	
	if (previeousHaveCard && nextHaveCard)
	{
		returnCard->PrevieousCard->NextCard = returnCard->NextCard;
		returnCard->NextCard->PrevieousCard = returnCard->PrevieousCard;
	}
	else if (previeousHaveCard && !nextHaveCard)
	{
		returnCard->PrevieousCard->NextCard = nullptr;
	}
	else if (!previeousHaveCard && nextHaveCard)
	{
		returnCard->NextCard->PrevieousCard = nullptr;
	}
	returnCard->PrevieousCard = nullptr;
	returnCard->NextCard = nullptr;

	return returnCard;
}

void GamePlay::SetDeckManager(DeckManager obj)
{
	DeckManagerObj = obj;
}

GamePlay::GamePlay()
{
	Prologue = "Welcome to Video Poker!";
	YourMoneyDes = "You have started with $";
	YoursCardDes = "Your hand contains:";
	YouPayDes = "You pay a $1 ante and now have $";
	GameOverDes = "You lost all your money. Game Over!";
	ChoiceTimeDes = "OPTIONS...\n- Type the letters for the cards you wish to keep. (i.e., ""acd"")\n- Type ""deck"" to view the cards remaining in the deck.\n- Type ""none"" to discard all cards in your hand.\n- Type ""all"" to keep all cards in your hand.\n- Type ""exit"" to exit the game.\n- Type ""swap"" to CHEAT and swap a card in your hand with one in the deck.\nYOUR CHOICE : ";
	DeckNumberDes = "The deck contains %n cards.";
	LastChoiceDes = "You kept %n and drew %n cards";

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
