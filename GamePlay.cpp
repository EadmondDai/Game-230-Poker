#include "GamePlay.h"

void GamePlay::ShowHand()
{


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
