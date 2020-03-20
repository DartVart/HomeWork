#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int sizeOfSecretNumber = 4;
const int maxSizeOfString = 5;

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
    for (int i = 1; i < sizeOfSecretNumber; i++)
    {
        do
        {
            newDigit = rand() % 10;
        } while (isDigitInNumber(secretNumber, newDigit, sizeOfSecretNumber));

        secretNumber[i] = newDigit;
    }
}

void representGuessAsArray(int guessAsInteger, int guessAsArray[])
{
    int lastDigit = 0;
    for (int i = sizeOfSecretNumber - 1; i >= 0; i--)
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

    for (int i = 0; i < sizeOfSecretNumber; i++)
    {
        if (isDigitInNumber(secretNumber, guessAsArray[i], sizeOfSecretNumber))
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

int convertCharToDigit(char symbol)
{
    return symbol - '0';
}

void getActionFromConsole(GameAction* action)
{
    // validation of input
    char* inputString = (char*) calloc(maxSizeOfString, sizeof(char));
    bool isCorrectInput = false;
    while (!isCorrectInput)
    {
        printf("If you want to exit, enter 0, if you want to continue, enter 1:\n");
        fflush(stdin);
        scanf("%2s", inputString);

        isCorrectInput = strcmp(inputString, "1") == 0 || strcmp(inputString, "0") == 0;
        if (!isCorrectInput)
        {
            printf("Please enter a valid value.\n");
        }
    }

    *action = convertCharToDigit(inputString[0]);
    free(inputString);
}

void playBullsAndCowsMatch(int lengthOfSecretNumber)
{
    int* guessAsArray = (int*) calloc(lengthOfSecretNumber, sizeof(int));
    int* secretNumber = (int*) calloc(lengthOfSecretNumber, sizeof(int));
    setSecretNumber(secretNumber);

    int guessAsInteger = 0;
    int attemptNumber = 0;
    Answer answer = {0, 0};

    while (answer.bulls != lengthOfSecretNumber)
    {
        attemptNumber++;
        printf("Enter a supposed number:");
        scanf("%d", &guessAsInteger);
        representGuessAsArray(guessAsInteger, guessAsArray);
        getAnswer(guessAsArray, secretNumber, &answer);
        printf("Attempt %d: %d -> %d bulls; %d cows.\n", attemptNumber, guessAsInteger, answer.bulls, answer.cows);
    }
    printf("Awesome! You win!\n");

    free(guessAsArray);
    free(secretNumber);
}

void playBullsAndCows(int lengthOfSecretNumber)
{
    GameAction action = CONTINUE;
    printForeword();

    getActionFromConsole(&action);

    while (action != EXIT)
    {
        printf("-----------------NEW GAME------------------\n");

        playBullsAndCowsMatch(lengthOfSecretNumber);

        getActionFromConsole(&action);
    }
}

int main()
{
    srand(time(NULL));

    playBullsAndCows(sizeOfSecretNumber);

    return 0;
}