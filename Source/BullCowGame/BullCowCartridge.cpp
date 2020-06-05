// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cows game!"));
    PrintLine(TEXT("Please press [Enter] to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("World");
}

/*Basic game loop
1. Generate the isogram with predefined hardcoded word length, 
   set amount of lives to hardcoded value, 
2. Display rules, the amount of lives left, number of letters in target isogram.
---Start guessing loop--- 
3. If amount of lives is 0 display loosing message and exit the loop
3. Prompt for a guess
4. If guess is correct
    a. Display winning message exit the loop
5. If guess is not correct
    a. If entered text is not an isogram or is different length 
       than the original word display the warning and continue the loop.     
    b. If entered text is not correct but is in correct format
       and it is last live display loosing message and exit loop.
    c. If entered text is not correct but is in correct format
       calculate and display bulls and cows, reduce lives by 1.  
---End guessing loop--- 
*/