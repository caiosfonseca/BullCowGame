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

    
    // Check if Isogram
    // Prompt to Guess Again
    // Check Right Number of Char
    // Prompt to Guess Again

    // Remove Life
    
    // Check if Lives > 0
    // If Yes GuessAgain
    // Show Lives Left
    // If No Show Game Over And HiddenWord?
    // Prompt to Play Again, Press Enter to Play Again?
    // Check User input
    // PlayAgain or Quit
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
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (HiddenWord.ToLower() == Guess.ToLower())
	{
		PrintLine(TEXT("You got it right mate!"));
		EndGame();
	}
	else
	{
		PrintLine(TEXT("You lost a life! You now have %i lives!"), --Lives);
		if (Lives > 0)
		{
			if (HiddenWord.Len() != Guess.Len())
			{
				PrintLine(TEXT("Sorry, try guessing again!\n You have %i Lives remaining"), Lives);
			}
		}
		else
		{
			PrintLine(TEXT("You have lost!"));
			EndGame();
		}
	}
}