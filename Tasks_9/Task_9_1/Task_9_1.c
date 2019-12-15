#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stringReading.h"

const int maxSizeOfString = 1000;

typedef enum State
{
    start = 0,
    signOfMantissa = 1,
    integerPart = 2,
    dot = 3,
    fractionalPart = 4,
    exponentSymbol = 5,
    signOfExponent = 6,
    exponentPart = 7,
    end = 8,
    fail = 9
} State;

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool isSign(char symbol)
{
    return symbol == '-' || symbol == '+';
}

bool isDot(char symbol)
{
    return symbol == '.';
}

bool isExponentSymbol(char symbol)
{
    return symbol == 'E';
}

bool isEndOfStringSymbol(char symbol)
{
    return symbol == '\0';
}

void processStart(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = integerPart;
    }
    else if (isSign(symbol))
    {
        *state = signOfMantissa;
    }
    else
    {
        *state = fail;
    }
}

void processSignOfMantissa(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = integerPart;
    }
    else
    {
        *state = fail;
    }
}

void processIntegerPart(char symbol, State* state)
{
    if (isDot(symbol))
    {
        *state = dot;
    }
    else if (isEndOfStringSymbol(symbol))
    {
        *state = end;
    }
    else if (isExponentSymbol(symbol))
    {
        *state = exponentSymbol;
    }
    else if (!isDigit(symbol))
    {
        *state = fail;
    }
}

void processDot(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = fractionalPart;
    }
    else
    {
        *state = fail;
    }
}

void processFractionalPart(char symbol, State* state)
{
    if (isEndOfStringSymbol(symbol))
    {
        *state = end;
    }
    else if (isExponentSymbol(symbol))
    {
        *state = exponentSymbol;
    }
    else if (!isDigit(symbol))
    {
        *state = fail;
    }
}

void processExponentSymbol(char symbol, State* state)
{
    if (isSign(symbol))
    {
        *state = signOfExponent;
    }
    else if (isDigit(symbol))
    {
        *state = exponentPart;
    }
    else
    {
        *state = fail;
    }
}

void processSignOfExponent(char symbol, State* state)
{
    if (isDigit(symbol))
    {
        *state = exponentPart;
    }
    else
    {
        *state = fail;
    }
}

void processExponentPart(char symbol, State* state)
{
    if (isEndOfStringSymbol(symbol))
    {
        *state = end;
    }
    else if (!isDigit(symbol))
    {
        *state = fail;
    }
}

bool isRealNumber(const char* checkingString)
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
            case signOfMantissa:
            {
                processSignOfMantissa(currentSymbol, &state);
                break;
            }
            case integerPart:
            {
                processIntegerPart(currentSymbol, &state);
                break;
            }
            case dot:
            {
                processDot(currentSymbol, &state);
                break;
            }
            case fractionalPart:
            {
                processFractionalPart(currentSymbol, &state);
                break;
            }
            case exponentSymbol:
            {
                processExponentSymbol(currentSymbol, &state);
                break;
            }
            case signOfExponent:
            {
                processSignOfExponent(currentSymbol, &state);
                break;
            }
            case exponentPart:
            {
                processExponentPart(currentSymbol, &state);
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
    char* inputString = (char*) malloc(maxSizeOfString * sizeof(char));
    printf("Enter the string:\n");
    scanString(stdin, inputString, maxSizeOfString);
    if (isRealNumber(inputString))
    {
        printf("You entered a real number!");
    }
    else
    {
        printf("You entered not a real number.");
    }

    free(inputString);
    return 0;
}