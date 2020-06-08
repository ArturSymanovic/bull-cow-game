// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
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
        if (Input == HiddenWord){       
            PrintLine(TEXT("You have won!"));
            EndGame();
        } 
        else 
        {
            if (HiddenWord.Len() !=  Input.Len())
            {
                PrintLine(TEXT("The hidden word is %i characters long!\nPlease try again!"), HiddenWord.Len());      
            }
            else if (!IsIsogram(Input))
            {
                PrintLine(TEXT("The entered word is not an isogram!\nPlease try again!"));
            }
            else
            {        
                if (Lives > 2)
                {
                    PrintLine(TEXT("Wrong! You have got %i lives left!"), --Lives);                    
                }
                else if (Lives == 2)
                {
                    PrintLine(TEXT("Wrong! You have got only %i live left!"), --Lives);                    
                }
                else
                {
                    PrintLine(TEXT("Wrong! You have lost!"));
                    EndGame();
                }
            }
        }        
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


bool UBullCowCartridge::IsIsogram(const FString& Input)
{
    TMap<TCHAR, int32> temp;
    for (auto &&cr : Input)
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