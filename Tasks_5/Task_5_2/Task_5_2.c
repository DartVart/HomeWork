#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

const int maxSizeOfString = 1000;

int convertCharToDigit(char symbol)
{
    return symbol - '0';
}

bool isDigit(char symbol)
{
    return '0' <= symbol && '9' >= symbol;
}

double performOperation(double firstNumber, double secondNumber, char operator)
{
    switch (operator)
    {
        case '+':
        {
            return firstNumber + secondNumber;
            break;
        }

        case '-':
        {
            return firstNumber - secondNumber;
            break;
        }

        case '*':
        {
            return firstNumber * secondNumber;
            break;
        }

        case '/':
        {
            return firstNumber / secondNumber;
            break;
        }

        default:
        {
            break;
        }
    }
}

/* recordableNumber is the part of the number that was considered before the function call;
 * isScanNumber determines whether a digit was process before the function call. */
bool processSymbolWhenCalculatingPostfixForm(Stack* numbersInExpression, char checkingSymbol,
                                             int* recordableNumber, bool* isScanOfNumber)
{
    double firstNumberInOperation = 0.0;
    double secondNumberInOperation = 0.0;
    double resultOfOperation = 0.0;
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

        if (getStackSize(numbersInExpression) < 2)
        {
            return false;
        }

        secondNumberInOperation = popFromStack(numbersInExpression);
        firstNumberInOperation = popFromStack(numbersInExpression);
        resultOfOperation = performOperation(firstNumberInOperation, secondNumberInOperation, checkingSymbol);
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

    Stack *numbersInExpression = createStack();
    int lengthOfExpression = strlen(postfixExpression);

    char currentSymbol = '\000';
    int currentRecordableNumber = 0;
    bool isScanOfNumber = false;
    bool isBalanceOfOperatorsAndOperands = true;

    for (int i = 0; i < lengthOfExpression; i++)
    {
        currentSymbol = postfixExpression[i];

        isBalanceOfOperatorsAndOperands = processSymbolWhenCalculatingPostfixForm(numbersInExpression, currentSymbol,
                                                                                  &currentRecordableNumber, &isScanOfNumber);
        if (!isBalanceOfOperatorsAndOperands)
        {
            return false;
        }
    }

    isBalanceOfOperatorsAndOperands = getStackSize(numbersInExpression) == 1;

    if (!isBalanceOfOperatorsAndOperands)
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
    printf("Enter an expression in postfix notation (characters '+', '-', '*', '/' are allowed):");
    scanStringWithSpaces(stdin, postfixExpression, maxSizeOfString);

    double resultOfExpression = 0.0;
    bool isCorrectExpression = false;
    isCorrectExpression = calculatePostfixExpression(postfixExpression, &resultOfExpression);

    if (isCorrectExpression)
    {
        printf("%s = %lf", postfixExpression, resultOfExpression);
    }
    else
    {
        printf("You entered an incorrect expression!");
    }

    free(postfixExpression);
    return 0;
}