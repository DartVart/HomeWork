#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

const int maxSizeOfString = 1000;

bool isOperator(char symbol)
{
    return (symbol == '+' ||
            symbol == '-' ||
            symbol == '*' ||
            symbol == '/');
}

bool isDigit(char symbol)
{
    return '0' <= symbol && '9' >= symbol;
}

/* if the symbol isn't a digit, the function will return -1. */
int convertCharToDigit(char symbol)
{
    if (isDigit(symbol))
    {
        return symbol - '0';
    }
    else return -1;
}

bool performOperation(double firstNumber, double secondNumber, double* resultOfOperation, char operator)
{
    switch (operator)
    {
        case '+':
        {
            *resultOfOperation = firstNumber + secondNumber;
            break;
        }

        case '-':
        {
            *resultOfOperation = firstNumber - secondNumber;
            break;
        }

        case '*':
        {
            *resultOfOperation = firstNumber * secondNumber;
            break;
        }

        case '/':
        {
            if (secondNumber == 0.0)
            {
                return false;
            }
            *resultOfOperation = firstNumber / secondNumber;
            break;
        }

        default:
        {
            return false;
        }
    }
    return true;
}

/* recordableNumber is the part of the number that was considered before the function call;
 * isScanNumber determines whether a digit was process before the function call. */
bool processSymbolWhenCalculatingPostfixForm(Stack* numbersInExpression, char checkingSymbol,
                                             int* recordableNumber, bool* isScanOfNumber)
{
    int currentDigit = 0;

    if (isDigit(checkingSymbol))
    {
        *isScanOfNumber = true;
        currentDigit = convertCharToDigit(checkingSymbol);
        *recordableNumber = (*recordableNumber) * 10 + currentDigit;
    }
    else
    {
        if (*isScanOfNumber)
        {
            *isScanOfNumber = false;
            pushToStack(numbersInExpression, *recordableNumber);
            *recordableNumber = 0;
        }

        if (checkingSymbol == ' ')
        {
            return true;
        }

        if (getStackSize(numbersInExpression) < 2 || !isOperator(checkingSymbol))
        {
            return false;
        }

        double firstNumberInOperation = 0.0;
        double secondNumberInOperation = 0.0;
        double resultOfOperation = 0.0;
        bool isDivisionByZero = false;
        secondNumberInOperation = popFromStack(numbersInExpression);
        firstNumberInOperation = popFromStack(numbersInExpression);
        isDivisionByZero = !performOperation(firstNumberInOperation, secondNumberInOperation, &resultOfOperation,
                                             checkingSymbol);
        if (isDivisionByZero)
        {
            return false;
        }
        pushToStack(numbersInExpression, resultOfOperation);
    }
    return true;
}

/* The result will be written into resultOfExpression.
 * If the expression is incorrect or (postfixExpression == NULL), the function will return false and
 * the value of resultOfExpression will be 0. */
bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression)
{
    if (postfixExpression == NULL)
    {
        return false;
    }

    Stack* numbersInExpression = createStack();
    int lengthOfExpression = strlen(postfixExpression);

    char currentSymbol = '\0';
    int currentRecordableNumber = 0;
    bool isScanOfNumber = false;
    bool isCorrectExpression = true;

    for (int i = 0; i < lengthOfExpression; i++)
    {
        currentSymbol = postfixExpression[i];

        isCorrectExpression = processSymbolWhenCalculatingPostfixForm(numbersInExpression, currentSymbol,
                                                                      &currentRecordableNumber, &isScanOfNumber);
        if (!isCorrectExpression)
        {
            return false;
        }
    }

    isCorrectExpression = getStackSize(numbersInExpression) == 1;

    if (!isCorrectExpression)
    {
        *resultOfExpression = 0;
        return false;
    }

    *resultOfExpression = popFromStack(numbersInExpression);

    deleteStack(numbersInExpression);
    return true;
}

void scanStringWithSpaces(FILE* inputStream, char* stringBuffer, int maxLengthOfString)
{
    if (inputStream == NULL)
    {
        return;
    }
    fflush(inputStream);
    fgets(stringBuffer, maxLengthOfString, inputStream);
    int indexOfNewLineCharacter = strlen(stringBuffer) - 1;
    stringBuffer[indexOfNewLineCharacter] = '\0';
}

int main()
{
    char* postfixExpression = (char*) calloc(maxSizeOfString, sizeof(char));
    printf("Enter an expression in postfix notation (characters '+', '-', '*', '/' are allowed):\n");
    scanStringWithSpaces(stdin, postfixExpression, maxSizeOfString);

    double resultOfExpression = 0.0;
    bool isCorrectExpression = false;
    isCorrectExpression = calculatePostfixExpression(postfixExpression, &resultOfExpression);

    if (isCorrectExpression)
    {
        printf("Result of the expression: %lf", resultOfExpression);
    }
    else
    {
        printf("You entered an incorrect expression!");
    }

    free(postfixExpression);
    return 0;
}
