#include <string.h>
#include "notationOfExpression.h"
#include "stack.h"

const int maxSizeOfExpression = 1000;

bool isOperator(char symbol)
{
    return (symbol == '+' ||
            symbol == '-' ||
            symbol == '*' ||
            symbol == '/');
}

int convertCharToDigit(char symbol)
{
    return symbol - '0';
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


// If the string is full, the function will return false
bool addToEndOfString(char string[], char symbol, int maxSizeOfString)
{
    if (string == NULL)
    {
        return false;
    }

    int lengthOfString = strlen(string);
    if (lengthOfString == maxSizeOfString - 1)
    {
        return false;
    }
    string[lengthOfString] = symbol;
    return true;
}

// If it's impossible to add, the function will return false
bool addOperatorToEndOfExpression(char expression[], char operator, int maxLengthOfExpression)
{
    if (expression == NULL)
    {
        return false;
    }
    bool isCorrectAdding = addToEndOfString(expression, operator, maxLengthOfExpression) &&
                           addToEndOfString(expression, ' ', maxLengthOfExpression);
    return isCorrectAdding;
}

// indexOfDigit initially contains the index of the first digit of the rewritable number in infixExpression.
// After the function works, indexOfDigit will contain the index of the last digit of the number.
// If it's impossible to rewrite, the function will return false
bool rewriteNumberToPostfixExpression(char infixExpression[], char postfixExpression[], int* indexOfDigit,
                                      int maxLengthOfExpression)
{
    if (infixExpression == NULL || postfixExpression == NULL)
    {
        return false;
    }
    bool isCorrectRewriting = true;
    char currentSymbol = infixExpression[*indexOfDigit];
    do
    {
        isCorrectRewriting = addToEndOfString(postfixExpression, currentSymbol, maxLengthOfExpression);
        if (!isCorrectRewriting)
        {
            return false;
        }

        (*indexOfDigit)++;
        currentSymbol = infixExpression[*indexOfDigit];
    } while (isDigit(currentSymbol));

    (*indexOfDigit)--;
    isCorrectRewriting = addToEndOfString(postfixExpression, ' ', maxLengthOfExpression);
    return isCorrectRewriting;
}

// If it's impossible to process or the string is incorrect, the function will return false
bool processOperatorWhenConvertingToPostfix(char postfixExpression[], StackOfChar* symbols, char operator,
                                            int maxLengthOfExpression)
{
    if (symbols == NULL || postfixExpression == NULL)
    {
        return false;
    }
    char topOfStack = peekIntoStackOfChar(symbols);
    bool isCorrectProcessing = true;

    while (!isStackOfCharEmpty(symbols) &&
           topOfStack != '(' &&
           getPriority(topOfStack) >= getPriority(operator))
    {
        topOfStack = popFromStackOfChar(symbols);

        isCorrectProcessing = addOperatorToEndOfExpression(postfixExpression, topOfStack, maxLengthOfExpression);
        if (!isCorrectProcessing)
        {
            return false;
        }

        topOfStack = peekIntoStackOfChar(symbols);
    }

    pushToStackOfChar(symbols, operator);
    return true;
}

// If it's impossible to process or the string is incorrect, the function will return false
bool processClosingBracketWhenConvertingToPostfix(char postfixExpression[], StackOfChar* symbols, int maxLengthOfExpression)
{
    if (symbols == NULL || postfixExpression == NULL)
    {
        return false;
    }
    char topOfStack = popFromStackOfChar(symbols);
    bool isCorrectProcessing = true;

    while (topOfStack != '(')
    {
        isCorrectProcessing = !isStackOfCharEmpty(symbols) &&
                              addOperatorToEndOfExpression(postfixExpression, topOfStack, maxLengthOfExpression);
        if (!isCorrectProcessing)
        {
            return false;
        }

        topOfStack = popFromStackOfChar(symbols);
    }

    return true;
}

// If it's impossible to push or the string is incorrect, the function will return false
bool pushRemainingOperatorsToPostfixExpression(char postfixExpression[], StackOfChar* symbols, int maxLengthOfExpression)
{
    if (symbols == NULL || postfixExpression == NULL)
    {
        return false;
    }
    char currentSymbol = '\000';
    bool isCorrectProcessing = true;

    while (!isStackOfCharEmpty(symbols))
    {
        currentSymbol = popFromStackOfChar(symbols);

        isCorrectProcessing = currentSymbol != '(' &&
                              addOperatorToEndOfExpression(postfixExpression, currentSymbol, maxLengthOfExpression);

        if (!isCorrectProcessing)
        {
            return false;
        }
    }

    return true;
}

// indexOfSymbol is an index of a symbol in infixExpression
// If it's impossible to process or the string is incorrect, the function will return false
bool processSymbolWhenConvertingToPostfix(char infixExpression[], char postfixExpression[], StackOfChar* symbols,
                                          int* indexOfSymbol)
{
    if (infixExpression == NULL || postfixExpression == NULL || symbols == NULL)
    {
        return false;
    }
    bool isCorrectExpression = true;
    char currentSymbol = infixExpression[*indexOfSymbol];

    if (isDigit(currentSymbol))
    {
        isCorrectExpression = rewriteNumberToPostfixExpression(infixExpression, postfixExpression, indexOfSymbol,
                                                               maxSizeOfExpression);
    }
    else if (isOperator(currentSymbol))
    {
        isCorrectExpression = processOperatorWhenConvertingToPostfix(postfixExpression, symbols, currentSymbol,
                                                                     maxSizeOfExpression);
    }
    else if (currentSymbol == ')')
    {
        isCorrectExpression = processClosingBracketWhenConvertingToPostfix(postfixExpression, symbols, maxSizeOfExpression);
    }
    else if (currentSymbol == '(')
    {
        pushToStackOfChar(symbols, currentSymbol);
    }
    else if (currentSymbol != ' ')
    {
        return false;
    }

    return isCorrectExpression;
}

bool convertInfixToPostfixNotation(char infixExpression[], char postfixExpression[])
{
    if (infixExpression == NULL || postfixExpression == NULL)
    {
        return false;
    }
    int lengthOfInfixExpression = strlen(infixExpression);

    StackOfChar* symbols = createStackOfChar();
    bool isCorrectExpression = true;
    for (int indexOfNewSymbol = 0; indexOfNewSymbol < lengthOfInfixExpression; indexOfNewSymbol++)
    {
        isCorrectExpression = processSymbolWhenConvertingToPostfix(infixExpression, postfixExpression, symbols,
                                                                   &indexOfNewSymbol);
        if (!isCorrectExpression)
        {
            return false;
        }
    }

    isCorrectExpression = pushRemainingOperatorsToPostfixExpression(postfixExpression, symbols, maxSizeOfExpression);

    if (!isCorrectExpression)
    {
        return false;
    }

    deleteStackOfChar(symbols);
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
bool processSymbolWhenCalculatingPostfixForm(StackOfDouble* numbersInExpression, char checkingSymbol,
                                             int* recordableNumber, bool* isScanOfNumber)
{
    if (numbersInExpression == NULL)
    {
        return false;
    }
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
            pushToStackOfDouble(numbersInExpression, *recordableNumber);
            *recordableNumber = 0;
        }

        if (checkingSymbol == ' ')
        {
            return true;
        }

        if (getStackOfDoubleSize(numbersInExpression) < 2 || !isOperator(checkingSymbol))
        {
            return false;
        }

        secondNumberInOperation = popFromStackOfDouble(numbersInExpression);
        firstNumberInOperation = popFromStackOfDouble(numbersInExpression);
        resultOfOperation = performOperation(firstNumberInOperation, secondNumberInOperation, checkingSymbol);
        pushToStackOfDouble(numbersInExpression, resultOfOperation);
    }
    return true;
}

bool calculatePostfixExpression(char postfixExpression[], double* resultOfExpression)
{
    if (postfixExpression == NULL)
    {
        return false;
    }

    StackOfDouble* numbersInExpression = createStackOfDouble();
    int lengthOfExpression = strlen(postfixExpression);

    char currentSymbol = '\000';
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

    isCorrectExpression = getStackOfDoubleSize(numbersInExpression) == 1;

    if (!isCorrectExpression)
    {
        *resultOfExpression = 0;
        return false;
    }

    *resultOfExpression = popFromStackOfDouble(numbersInExpression);

    deleteStackOfDouble(numbersInExpression);
    return true;
}