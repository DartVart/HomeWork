#include <string.h>
#include "notationOfExpression.h"
#include "stack.h"

bool isOperator(char symbol)
{
    return (symbol == '+' ||
            symbol == '-' ||
            symbol == '*' ||
            symbol == '/' );
}

int convertCharToDigit(char symbol)
{
    return (int)symbol - (int)'0';
}

bool isDigit(char symbol)
{
    return '0' <= symbol && '9' >= symbol;
}

/* If the operator is incorrect, the function will return -1. */
int getPriority(char operator)
{
    switch (operator)
    {
        case '*':
        case '/':
        {
            return 1;
            break;
        }

        case '-':
        case '+':
        {
            return 0;
            break;
        }

        default:
        {
            return -1;
            break;
        }
    }
}

void addToEndOfString(char string[], char symbol, int* lengthOfString)
{
    string[*lengthOfString] = symbol;
    (*lengthOfString)++;
}

void addOperatorToEndOfExpression(char expression[], char operator, int* lengthOfExpression)
{
    addToEndOfString(expression, operator, lengthOfExpression);
    addToEndOfString(expression, ' ', lengthOfExpression);
}

bool convertInfixToPostfixNotation(char infixExpression[], char postfixExpression[])
{
    int lengthOfInfixExpression = strlen(infixExpression);

    StackOfChar* stackOfChar = createStackOfChar();
    char topOfStack = '\000';

    int lengthOfPostfixExpression = 0;
    char currentSymbol = '\000';
    for (int indexOfNewSymbol = 0; indexOfNewSymbol < lengthOfInfixExpression; indexOfNewSymbol++)
    {
        currentSymbol = infixExpression[indexOfNewSymbol];

        if (isDigit(currentSymbol))
        {
            // Scanning a new number
            do
            {
                addToEndOfString(postfixExpression, currentSymbol, &lengthOfPostfixExpression);
                indexOfNewSymbol++;
                currentSymbol = infixExpression[indexOfNewSymbol];
            } while (isDigit(currentSymbol));

            addToEndOfString(postfixExpression, ' ', &lengthOfPostfixExpression);
        }

        if (isOperator(currentSymbol))
        {
            topOfStack = peekIntoStackOfChar(stackOfChar);

            while (!isStackOfCharEmpty(stackOfChar) &&
                   topOfStack != '(' &&
                   getPriority(topOfStack) >= getPriority(currentSymbol))
            {
                topOfStack = popFromStackOfChar(stackOfChar);

                addOperatorToEndOfExpression(postfixExpression, topOfStack, &lengthOfPostfixExpression);

                topOfStack = peekIntoStackOfChar(stackOfChar);
            }

            pushToStackOfChar(stackOfChar, currentSymbol);
        }
        else if (currentSymbol == ')')
        {
            topOfStack = popFromStackOfChar(stackOfChar);

            while (topOfStack != '(')
            {
                if (isStackOfCharEmpty(stackOfChar))
                {
                    return false;
                }

                addOperatorToEndOfExpression(postfixExpression, topOfStack, &lengthOfPostfixExpression);

                topOfStack = popFromStackOfChar(stackOfChar);
            }
        }
        else if (currentSymbol == '(')
        {
            pushToStackOfChar(stackOfChar, currentSymbol);
        }
    }

    while (!isStackOfCharEmpty(stackOfChar))
    {
        currentSymbol = popFromStackOfChar(stackOfChar);

        if (currentSymbol == '(')
        {
            return false;
        }

        addOperatorToEndOfExpression(postfixExpression, currentSymbol, &lengthOfPostfixExpression);
    }

    deleteStackOfChar(stackOfChar);

    return true;
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
            return (double)firstNumber / (double)secondNumber;
            break;
        }

        default:
        {
            break;
        }
    }
}

bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression)
{
    StackOfDouble *numbersInExpression = createStackOfDouble();
    int lengthOfExpression = strlen(postfixExpression);

    char currentSymbol = '\000';
    int currentRecordableNumber = 0;
    double firstNumberInOperation = 0.0;
    double secondNumberInOperation = 0.0;
    double resultOfCurrentOperation = 0.0;
    int currentDigit = 0;
    bool isScanOfNumber = false;
    for (int i = 0; i < lengthOfExpression; i++)
    {
        currentSymbol = postfixExpression[i];

        if (isDigit(currentSymbol))
        {
            isScanOfNumber = true;
            currentDigit = convertCharToDigit(currentSymbol);
            currentRecordableNumber = currentRecordableNumber * 10 + currentDigit;
        }
        else
        {
            if (isScanOfNumber)
            {
                isScanOfNumber = false;
                pushToStackOfDouble(numbersInExpression, currentRecordableNumber);
                currentRecordableNumber = 0;
            }

            if (currentSymbol == ' ')
            {
                continue;
            }

            if (getStackOfDoubleSize(numbersInExpression) < 2)
            {
                return false;
            }

            secondNumberInOperation = popFromStackOfDouble(numbersInExpression);
            firstNumberInOperation = popFromStackOfDouble(numbersInExpression);
            resultOfCurrentOperation = performOperation(firstNumberInOperation, secondNumberInOperation, currentSymbol);
            pushToStackOfDouble(numbersInExpression, resultOfCurrentOperation);
        }
    }

    if (getStackOfDoubleSize(numbersInExpression) != 1)
    {
        *resultOfExpression = 0.0;
        return false;
    }

    *resultOfExpression = popFromStackOfDouble(numbersInExpression);

    deleteStackOfDouble(numbersInExpression);
    return true;
}
