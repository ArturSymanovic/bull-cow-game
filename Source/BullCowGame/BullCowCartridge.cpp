// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Below loaqds words from a file into a list of FString
    // const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    // FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    
    //The below loads only isograms from the file (using predicate and lambda functions)
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(
        WordList,
        *WordListPath,
        [this](const FString& Word) { return IsLongIsogram(Word); });
    
    PrintLine(TEXT("Press [TAB] to enable typing into the terminal..."));
    SetupGame();   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);                
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = WordList[FMath::RandRange(0, WordList.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to the Bull Cows game!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("Please type your guess and press [Enter]!"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press [Enter] to play again..."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    TMap<TCHAR, int32> temp;
    for (auto &&cr : Word.ToLower())
    {    
        if (!temp.Contains(cr))
        {
            temp.Add(cr, 0);
        }
        else
        {           
            return false;                
        }        
    }
    return true;
}

bool UBullCowCartridge::IsLongIsogram(const FString& Word) const
{
    if (Word.Len()<4)
    {
        return false;
    }
    TMap<TCHAR, int32> temp;
    for (auto &&cr : Word.ToLower())
    {    
        if (!temp.Contains(cr))
        {
            temp.Add(cr, 0);
        }
        else
        {           
            return false;                
        }        
    }
    return true;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord){       
        PrintLine(TEXT("Correct! You have won!"));
        EndGame();
        return;
    } 

    if (HiddenWord.Len() !=  Guess.Len())
    {
        PrintLine(TEXT("The hidden word is %i characters long!\nPlease try again!"), HiddenWord.Len());      
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The entered word is not an isogram!\nPlease try again!"));
        return;
    }
      
    if (Lives > 1)
    {
        PrintLine(TEXT("Wrong! Lives left: %i. Please try another word!"), --Lives);
        return;                    
    }
    
    PrintLine(TEXT("Wrong! You have lost!"));
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
    EndGame();   
}
