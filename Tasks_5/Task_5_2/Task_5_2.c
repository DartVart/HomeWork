#include <stdio.h>
#include <string.h>
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

/* The result will be written into resultOfExpression.
 * If the expression is incorrect, the function will return false and
 * the value of resultOfExpression will be 0.*/
bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression)
{
    Stack *numbersInExpression = createStack();
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
                pushToStack(numbersInExpression, currentRecordableNumber);
                currentRecordableNumber = 0;
            }

            if (currentSymbol == ' ')
            {
                continue;
            }

            if (getStackSize(numbersInExpression) < 2)
            {
                return false;
            }

            secondNumberInOperation = popFromStack(numbersInExpression);
            firstNumberInOperation = popFromStack(numbersInExpression);
            resultOfCurrentOperation = performOperation(firstNumberInOperation, secondNumberInOperation, currentSymbol);
            pushToStack(numbersInExpression, resultOfCurrentOperation);
        }
    }

    if (getStackSize(numbersInExpression) != 1)
    {
        *resultOfExpression = 0;
        return false;
    }

    *resultOfExpression = popFromStack(numbersInExpression);


    deleteStack(numbersInExpression);
    return true;
}

void scanStringWithSpaces(FILE* inputStream, char* stringBuffer)
{
    fflush(inputStream);
    scanf("%[^\n]", stringBuffer);
}

int main()
{
    char postfixExpression[maxSizeOfString] = "";
    printf("Enter an expression in postfix notation (characters '+', '-', '*', '/' are allowed):");
    scanStringWithSpaces(stdin, postfixExpression);

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

    return 0;
}
