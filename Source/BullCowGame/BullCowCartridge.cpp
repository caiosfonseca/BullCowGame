// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	
	Isograms = GetValidWords(Words);

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking player guess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows game!"));
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;
    PrintLine(FString::Printf(TEXT("Guess the %i letter word"), HiddenWord.Len()));
    // PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord);// Debug line
    PrintLine(TEXT("You have %i lives!"), Lives);

    // Prompt Player for guess
    PrintLine(TEXT("Type in your guess and \nPress enter to submit!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
	const FBullCowCount Count = GetBullCows(Guess);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
	
	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);	
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for (int32 i = 0; i < Word.Len(); ++i)
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;

	for(FString Word : WordList)
	{
		if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}

	return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount Count; 

	// For every index of Guess is same as index Hidden, BullCount ++
	// if not a bull, was it a cow? If yes CowCount ++
	for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); ++GuessIndex)
	{
		if(Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}

		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); ++HiddenIndex)
		{
			if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}
		