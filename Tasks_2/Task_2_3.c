#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int lengthOfSecretNumber = 4;

typedef enum GameAction GameAction;
enum GameAction
{
    EXIT,
    CONTINUE
};

typedef struct Answer Answer;
struct Answer
{
    int bulls;
    int cows;
};

bool isDigitInNumber(int number[], int digit, int lengthOfNumber)
{
    for (int i = 0; i < lengthOfNumber; i++)
    {
        if (number[i] == digit)
        {
            return true;
        }
    }
    return false;
}

void setSecretNumber(int secretNumber[])
{
    int newDigit = 0;
    secretNumber[0] = rand() % 9 + 1;
    for (int i = 1; i < lengthOfSecretNumber; i++)
    {
        do
        {
            newDigit = rand() % 10;
        } while (isDigitInNumber(secretNumber, newDigit, lengthOfSecretNumber));

        secretNumber[i] = newDigit;
    }
}

void representGuessAsArray(int guessAsInteger, int guessAsArray[])
{
    int lastDigit = 0;
    for (int i = lengthOfSecretNumber - 1; i >= 0; i--)
    {
        lastDigit = guessAsInteger % 10;
        guessAsArray[i] = lastDigit;
        guessAsInteger /= 10;
    }
}

void getAnswer(int guessAsArray[], int secretNumber[], Answer* answer)
{
    answer->bulls = 0;
    answer->cows = 0;

    for (int i = 0; i < lengthOfSecretNumber; i++)
    {
        if (isDigitInNumber(secretNumber, guessAsArray[i], lengthOfSecretNumber))
        {
            if (guessAsArray[i] == secretNumber[i])
            {
                answer->bulls++;
            }
            else
            {
                answer->cows++;
            }
        }
    }
}

void printForeword()
{
    printf("Welcome! This is the Bulls and Cows game."
           " The rules are simple: you need to guess the 4-digit number hidden by the computer "
           "(the numbers in the number do not repeat). "
           "For each attempt you make, you will get the number of \"bulls\" "
           "(the number of digits in your number that match the places and value with the digits of the guessed number) "
           "and the number of \"cows\" (the number of digits in your number "
           "that match only the values with the digits of the guessed number).\n"
           "Example:\n"
           "Secret number: 2530\n"
           "Your guess: 2093\n"
           "Output: \"Attempt 1: 2093 -> 1 bulls; 2 cows.\"\n");
}

void getActionFromConsole(GameAction* action)
{
    printf("If you want to exit, enter 0, if you want to continue, enter 1:\n");
    scanf("%d", action);
}

int main()
{
    srand(time(NULL));

    int guessAsInteger = 0;
    int guessAsArray[lengthOfSecretNumber] = {0};
    int secretNumber[lengthOfSecretNumber] = {0};
    int attemptNumber = 0;
    GameAction action = CONTINUE;
    Answer answer = {0, 0};

    printForeword();

    getActionFromConsole(&action);

    while (action != EXIT)
    {
        printf("-----------------NEW GAME------------------\n");

        setSecretNumber(secretNumber);

        while (answer.bulls != lengthOfSecretNumber)
        {
            attemptNumber++;
            printf("Enter a supposed number:");
            scanf("%d", &guessAsInteger);
            representGuessAsArray(guessAsInteger, guessAsArray);
            getAnswer(guessAsArray, secretNumber, &answer);
            printf("Attempt %d: %d -> %d bulls; %d cows.\n", attemptNumber, guessAsInteger, answer.bulls, answer.cows);
        }
        attemptNumber = 0;
        answer.bulls = 0;
        answer.cows = 0;

        printf("Awesome! You win!\n");
        getActionFromConsole(&action);
    }

    return 0;
}