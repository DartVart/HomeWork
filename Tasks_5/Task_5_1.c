#include <stdio.h>
#include <string.h>
#include "charStack.h"

const int maxSizeOfString = 1000;

bool isOperator(char symbol)
{
    return (symbol == '+' ||
            symbol == '-' ||
            symbol == '*' ||
            symbol == '/' );
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

/* This function doesn't detect all incorrect expressions. */
bool convertInfixToPostfixNotation(char infixExpression[], char postfixExpression[])
{
    int lengthOfInfixExpression = strlen(infixExpression);

    Stack* stackOfChar = createStack();
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
            topOfStack = peekIntoStack(stackOfChar);

            while (!isStackEmpty(stackOfChar) &&
                   topOfStack != '(' &&
                   getPriority(topOfStack) >= getPriority(currentSymbol))
            {
                topOfStack = popFromStack(stackOfChar);

                addOperatorToEndOfExpression(postfixExpression, topOfStack, &lengthOfPostfixExpression);

                topOfStack = peekIntoStack(stackOfChar);
            }

            pushToStack(stackOfChar, currentSymbol);
        }
        else if (currentSymbol == ')')
        {
            topOfStack = popFromStack(stackOfChar);

            while (topOfStack != '(')
            {
                if (isStackEmpty(stackOfChar))
                {
                    return false;
                }

                addOperatorToEndOfExpression(postfixExpression, topOfStack, &lengthOfPostfixExpression);

                topOfStack = popFromStack(stackOfChar);
            }
        }
        else if (currentSymbol == '(')
        {
            pushToStack(stackOfChar, currentSymbol);
        }
    }

    while (!isStackEmpty(stackOfChar))
    {
        currentSymbol = popFromStack(stackOfChar);

        if (currentSymbol == '(')
        {
            return false;
        }

        addOperatorToEndOfExpression(postfixExpression, currentSymbol, &lengthOfPostfixExpression);
    }

    deleteStack(stackOfChar);

    return true;
}

void scanStringWithSpaces(FILE* inputStream, char* stringBuffer)
{
    fflush(inputStream);
    scanf("%[^\n]", stringBuffer);
}

int main()
{
    char infixExpression[maxSizeOfString] = "";
    char postfixExpression[maxSizeOfString] = "";

    printf("Enter an expression in infix notation:");
    scanStringWithSpaces(stdin, infixExpression);

    bool isInfixNotationCorrect = convertInfixToPostfixNotation(infixExpression, postfixExpression);
    if (isInfixNotationCorrect)
    {
        printf("The expression \"%s\" in postfix notation: \n"
               "%s", infixExpression, postfixExpression);
    }
    else
    {
        printf("You entered an incorrect expression!");
    }

    return 0;
}