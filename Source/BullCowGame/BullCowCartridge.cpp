// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    //PrintLine(FString::Printf(TEXT("The HiddenWord is %s"), *HiddenWord));
    // PrintLine already uses Printf, so we don't need to do it
    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord); 

    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows game!"));
    PrintLine(FString::Printf(TEXT("Guess the %i letter word"), HiddenWord.Len()));
    
    // Prompt Player for guess
    PrintLine(TEXT("Type in your guess, press enter to submit!"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

   
    // Checking player for guess
    if (HiddenWord.ToLower() == Input.ToLower())
    {
        PrintLine(TEXT("You got it right mate!"));
    }
    else
    {
		if (HiddenWord.Len() != Input.Len())
		{
            PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
		}
        else
        {
			// Add remaining lives to the text
			PrintLine(TEXT("You lost, try again champ!"));
        }
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
	HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
}