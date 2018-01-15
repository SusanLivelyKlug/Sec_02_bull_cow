/*
 * Console executable.
 * Acts as a View in a MVC Pattern.
 * Responsible for all user interaction.
 * Game logic in FBullCowGame class
 *
 * Udemy C++ Unreal course Section 02
 * Susan Lively Klug
 * January 2018
 */

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside of a class
void PrintIntro();
void PrintSummary();
FText GetValidGuess();
void PrintGuess( FText );
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame;	//Instantiate a new game

// The entry point for our application
int main()
{
	do {
		BCGame.Reset();
		PrintIntro();
		PlayGame();
	} while ( AskToPlayAgain() );

	std::cout << std::endl;
	return 0; //exit game
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n" << std::endl;
	std::cout << "Bulls are the number of letters that are correct and in the correct position." << std::endl;
	std::cout << "Cows are the number of letters that are correct but in the wrong position." << std::endl;
	std::cout << std::endl;
	std::cout << "          \\__,,,__/   ,__.__,		" << std::endl;
	std::cout << "          <{ 0 0 }>  <( o o )>		" << std::endl;
	std::cout << "    ________\\ @ /      \\ @ /________			" << std::endl;
	std::cout << "   /| bull  | U          U| cow   |\\		" << std::endl;
	std::cout << "  / |_______|             |_______| \\		" << std::endl;
	std::cout << " #  ||`    ||             ||   uu||  #	" << std::endl;
	std::cout << "    ^^     ^^             ^^     ^^		"  << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter a five letter isogram (a word with no repeating letters)." << std::endl;
	
	return;
}

// Plays a single game to completion
void PlayGame() 
{
	int32 MaxTries = BCGame.GetMaxTries();
	int32 CurrentTry = BCGame.GetCurrentTry();
	
	// loop asking for guesses while the game is not won
	// and there are still tries remaining
	while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		PrintGuess( Guess );
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << ".\n\n";
	}
	PrintSummary();
	
	return;
}

// Print out end of game message
void PrintSummary()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "Congratulations, You Win!\n"; 
	}
	else 
	{
		std::cout << "Out of Tries.\n"; 
	}
	return;
}

// Get a guess from the player, loop until valid
FText GetValidGuess() 
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	int32 guesses_left = BCGame.GetMaxTries() - CurrentTry+1;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		if (guesses_left > 0) {
			std::cout << "Guess number " << CurrentTry << " only " << guesses_left << " guesses left.\n";
		}
		else std::cout << "Last Try!";

		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Wrong word length, please enter a " << BCGame.GetHiddenWordLength() << " length word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Not Lowercase.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Not Isogram. Isograms have no repeating letters.\n";
			break;
		default:
			break; // assume guess is valid
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;

}

// Repeat the guess back to them
void PrintGuess( FText Guess ) 
{
	std::cout << "You guessed " << Guess << std::endl;
	return;
}

// Play again?
bool AskToPlayAgain()
{
	FText Response = "";

	std::cout << "Would you like to play again with the same word? (y/n)\n";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

