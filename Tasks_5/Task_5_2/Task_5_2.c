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
    return -1;
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

/* Initially 'indexOfDigit' contains the index of the first digit of the number in the string.
 * After the function is completed, 'indexOfDigit' will contain the index of the last digit of the number. */
bool scanNumberFromString(int* number, const char* string, int* indexOfDigit)
{
    *number = 0;
    char currentSymbol = string[*indexOfDigit];
    if (!isDigit(currentSymbol))
    {
        return false;
    }

    int currentDigit = 0;
    do
    {
        currentDigit = convertCharToDigit(currentSymbol);
        *number = (*number) * 10 + currentDigit;
        (*indexOfDigit)++;
        currentSymbol = string[*indexOfDigit];
    } while (isDigit(currentSymbol));

    (*indexOfDigit)--;
    return true;
}

/* The function processes the symbol when calculating in postfix notation.
 * Initially the 'indexOfSymbol' contains the index of the checking character.
 * If a number was read, then the 'indexOfSymbol' will contain the index of the last digit of the number. */
bool processSymbolWhenCalculating(Stack* numbersInExpression, char checkingSymbol,
                                  char* postfixExpression, int* indexOfSymbol)
{
    if (isDigit(checkingSymbol))
    {
        int recordableNumber = 0;
        scanNumberFromString(&recordableNumber, postfixExpression, indexOfSymbol);
        pushToStack(numbersInExpression, recordableNumber);
    }
    else if (checkingSymbol != ' ')
    {
        if (getStackSize(numbersInExpression) < 2 || !isOperator(checkingSymbol))
        {
            return false;
        }

        double secondNumberInOperation = popFromStack(numbersInExpression);
        double firstNumberInOperation = popFromStack(numbersInExpression);
        double resultOfOperation = 0.0;
        bool isDivisionByZero = false;
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

/* If the expression is incorrect or (postfixExpression == NULL), the function will return false.
 * The result will be contained in the 'numbersInExpression'.
 * This function only processes the string of the postfix expression
 * without checking the calculating is correct. */
bool processPostfixExpressionWhenCalculating(char* postfixExpression, Stack* numbersInExpression)
{
    if (postfixExpression == NULL || numbersInExpression == NULL)
    {
        return false;
    }

    int lengthOfExpression = strlen(postfixExpression);
    char currentSymbol = '\0';
    bool isCorrectExpression = true;
    for (int i = 0; i < lengthOfExpression; i++)
    {
        currentSymbol = postfixExpression[i];

        isCorrectExpression = processSymbolWhenCalculating(numbersInExpression, currentSymbol, postfixExpression, &i);
        if (!isCorrectExpression)
        {
            return false;
        }
    }
    return true;
}

bool isCorrectCompletionOfCalculating(Stack* numbersInExpression)
{
    return getStackSize(numbersInExpression) == 1;
}

/* The result will be written into resultOfExpression.
 * If the calculating is incorrect or (postfixExpression == NULL), the function will return false and
 * the value of resultOfExpression will be 0. */
bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression)
{
    if (postfixExpression == NULL)
    {
        return false;
    }

    Stack* numbersInExpression = createStack();
    bool isCorrectExpression = processPostfixExpressionWhenCalculating(postfixExpression, numbersInExpression) &&
                               isCorrectCompletionOfCalculating(numbersInExpression);

    if (!isCorrectExpression)
    {
        *resultOfExpression = 0;
    }
    else
    {
        *resultOfExpression = popFromStack(numbersInExpression);
    }
    deleteStack(numbersInExpression);
    return isCorrectExpression;
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
