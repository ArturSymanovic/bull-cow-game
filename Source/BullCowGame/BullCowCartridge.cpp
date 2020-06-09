// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    PrintLine(TEXT("%s"), *WordList[0]);
    //The below loads only isograms from the file (using predicate)
    // const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    // FFileHelper::LoadFileToStringArrayWithPredicate(
    //     WordList,
    //     *WordListPath,
    //     [this](const FString& Word) { return IsIsogram(Word); });
    
    PrintLine(TEXT("Press [TAB] to enable typing into the terminal..."));
    SetupGame();

    //PrintLine(FString::Printf(TEXT("The hidden word is %s"), *HiddenWord)); //Debug line
    
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
    HiddenWord = TEXT("cake");
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

bool UBullCowCartridge::IsIsogram(const FString& Input) const
{
    TMap<TCHAR, int32> temp;
    for (auto &&cr : Input.ToLower())
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
