#include <stdio.h>
#include <stdlib.h>
#include "stringReading.h"

typedef enum State
{
    start = 0,
    firstDigitOfYear = 1,
    secondDigitOfYear = 2,
    qualificationLevel = 3,
    firstGroupDigit = 4,
    groupNumber = 5,
    hyphen = 6,
    firstM = 7,
    secondM = 8,
    end = 9,
    fail = 10
} State;

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool isQualificationLevel(char symbol)
{
    return symbol == 'B' ||
           symbol == 'M' ||
           symbol == 'S';
}

void processStart(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = firstDigitOfYear;
    }
    else
    {
        *state = fail;
    }
}

void processFirstDigitOfYear(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = secondDigitOfYear;
    }
    else
    {
        *state = fail;
    }
}

void processSecondDigitOfYear(char symbol, State* state)
{
    if (isQualificationLevel(symbol))
    {
        *state = qualificationLevel;
    }
    else
    {
        *state = fail;
    }
}

void processQualificationLevel(char symbol, State* state)
{
    if (symbol == '1')
    {
        *state = firstGroupDigit;
    }
    else if (isDigit(symbol))
    {
        *state = groupNumber;
    }
    else
    {
        *state = fail;
    }
}

void processFirstGroupDigit(char symbol, State* state)
{
    if (symbol == '0')
    {
        *state = groupNumber;
    }
    else
    {
        *state = fail;
    }
}

void processGroupNumber(char symbol, State* state)
{
    if (symbol == '-')
    {
        *state = hyphen;
    }
    else
    {
        *state = fail;
    }
}

void processHyphen(char symbol, State* state)
{
    if (symbol == 'm')
    {
        *state = firstM;
    }
    else
    {
        *state = fail;
    }
}

void processFirstM(char symbol, State* state)
{
    if (symbol == 'm')
    {
        *state = secondM;
    }
    else
    {
        *state = fail;
    }
}

void processSecondM(char symbol, State* state)
{
    if (symbol == '\0')
    {
        *state = end;
    }
    else
    {
        *state = fail;
    }
}

bool isGroupNumber(const char* checkingString)
{
    char currentSymbol = '\0';
    int currentIndex = 0;
    State state = start;
    while (state != fail && state != end)
    {
        currentSymbol = checkingString[currentIndex];
        switch (state)
        {
            case start:
            {
                processStart(currentSymbol, &state);
                break;
            }
            case firstDigitOfYear:
            {
                processFirstDigitOfYear(currentSymbol, &state);
                break;
            }
            case secondDigitOfYear:
            {
                processSecondDigitOfYear(currentSymbol, &state);
                break;
            }
            case qualificationLevel:
            {
                processQualificationLevel(currentSymbol, &state);
                break;
            }
            case firstGroupDigit:
            {
                processFirstGroupDigit(currentSymbol, &state);
                break;
            }
            case groupNumber:
            {
                processGroupNumber(currentSymbol, &state);
                break;
            }
            case hyphen:
            {
                processHyphen(currentSymbol, &state);
                break;
            }
            case firstM:
            {
                processFirstM(currentSymbol, &state);
                break;
            }
            case secondM:
            {
                processSecondM(currentSymbol, &state);
                break;
            }
            default:
            {
                break;
            }
        }
        currentIndex++;
    }
    return state != fail;
}

int main()
{
    printf("Enter the string:\n");
    char* inputString = getStringFromStream(stdin, readingWithSpaces);

    if (isGroupNumber(inputString))
    {
        printf("You entered a correct group number!");
    }
    else
    {
        printf("You entered an incorrect group number.");
    }

    free(inputString);
    return 0;
}