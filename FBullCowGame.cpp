/*
* The game logic
* Not view code or direct user interaction
* Simple guess the word game
 *
* Udemy C++ Unreal course Section 02
* Susan Lively Klug
* January 2018
*/

#pragma once
#include "FBullCowGame.h"

// to make syntax Unreal friendly
#include <map>
#define TMap std::map 

using int32 = int;

FBullCowGame::FBullCowGame(){Reset();} // default constructor

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

// Tune the game based on length of the hidden word.
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset() 
{
	const FString HIDDEN_WORD = "ant"; // This must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

// Check if string is all lower case
bool FBullCowGame::IsLowercase(FString Word) const
{
	char Letter;

	// check each letter if it is lower case
	for (auto Letter : Word) {
		if ( !islower( Letter ) ) { // not lower case
			return false;
		}
	}
	return true;
}

// Check if string is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	// create hash solution using TMap 
	TMap<char, bool> LetterSeen;

	// range based for loop through Word until end
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if there is a collision, notIsogram leave
			return false;
		} 
		else { // add the letter to the map
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

// Check if the guess has correct number of letters
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess)) {// if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {// if the guess isn't all lower case
		return EGuessStatus::Not_Lowercase;
	}
	else if ( Guess.length() != GetHiddenWordLength() ) {// if the guess is the wrong length
		return EGuessStatus::Wrong_Length;
	}
	else { return EGuessStatus::OK; }

}

// receives valid guess in Guess parameter
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// return variable
	FBullCowCount BullCowCount;

	MyCurrentTry++;

	// loop through letters in hidden word
	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) {
		// compare Guess against hidden isogram
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (Guess[i] == MyHiddenWord[j])
			{
				// if they're in the same place
				if (i == j) { //increment bulls
					BullCowCount.Bulls++;
				}
				else { // increment cow
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{ 
		bGameWon = true; 
	}
	else { 
		bGameWon = false; 
	}
	return BullCowCount;
}
