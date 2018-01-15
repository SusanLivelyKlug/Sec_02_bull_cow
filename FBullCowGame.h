/*
 * The game logic
 * Not view code or direct user interaction
 * Simple guess the word game
 *
 * Udemy C++ Unreal course Section 02
 * Susan Lively Klug
 * January 2018
 *
 * Known Issues:  a cntl-Z as input causes loop (cntl-C to kill loop)
 *
 * Future TODO List:
 * TODO Dictionary of isograms of specific length 
 * TODO User choice of word length
 * TODO User choice of repeat game with same word, or pick a new word 
 * TODO Session scoring
 * TODO Take out wording "only" number of guesses left, rework feedback.
 * 
 * Super cool future TODO that is out of scope and probably will never happen
 * Leaderboard and web interface for embedding game into a website
 * Much better ASCII art. 
 * Instead of text for number of bulls and cows, have ASCII symbols
 */
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};

class FBullCowGame 
{
public:
	FBullCowGame();								// Constructor

	int32 GetMaxTries() const;					// Get the maximum number of attempts
	int32 GetCurrentTry() const;				// What attempt is player on? How many tries left?
	int32 GetHiddenWordLength() const;			//

	bool IsGameWon() const;						// string to isogram compare somewhere need to output bulls and cows
	EGuessStatus CheckGuessValidity(FString);	

	void Reset();								
	FBullCowCount SubmitValidGuess(FString);	// counts bulls and cows and increases try number, assume valid guess

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
