// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    //PrintLine(FString::Printf(TEXT("The HiddenWord is %s"), *HiddenWord));
    // PrintLine already uses Printf, so we don't need to do it
    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); 
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking player guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows game!"));
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(FString::Printf(TEXT("Guess the %i letter word"), HiddenWord.Len()));
    PrintLine(TEXT("You have %i lives!"), Lives);

    // Prompt Player for guess
    PrintLine(TEXT("Type in your guess and \nPress enter to submit!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (HiddenWord.ToLower() == Guess.ToLower())
	{
		PrintLine(TEXT("You got it right mate!"));
		EndGame();
        return;
	}

	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again!\n You have %i Lives remaining"), Lives);
		return;
	}

	// Check if Isogram
	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letter, guess again!"));
		return;
	}

	//Remove a life
	PrintLine(TEXT("You lost a life!"));
	--Lives;

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have lost!"));
		PrintLine(TEXT("The word was %s"), *HiddenWord);
		EndGame();
		return;
	}

	//Show the player bulls and cows
	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
	// If Yes GuessAgain
	// Show Lives Left
	// If No Show Game Over And HiddenWord?
	// Prompt to Play Again, Press Enter to Play Again?
	// Check User input
	// PlayAgain or Quit

	
	
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	for (int32 i = 0; i < Word.Len()-1; ++i)
	{
		for (int32 j = i+1; j < Word.Len(); ++j)
		{
			if(Word[i] == Word[j])
			{
				return false;
			}
		}
	}
	return true;
}
		