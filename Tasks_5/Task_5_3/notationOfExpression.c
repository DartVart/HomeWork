#include <string.h>
#include <stdlib.h>
#include "notationOfExpression.h"
#include "stack.h"

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

/* If the symbol isn't a digit, the function will return -1. */
int convertCharToDigit(char symbol)
{
    if (isDigit(symbol))
    {
        return symbol - '0';
    }
    return -1;
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
        }

        case '-':
        case '+':
        {
            return 0;
        }

        default:
        {
            return -1;
        }
    }
}

/* If the string is full, the function will return false. */
bool addToEndOfString(char* string, char symbol, int maxSizeOfString)
{
    int lengthOfString = strlen(string);
    if (lengthOfString == maxSizeOfString)
    {
        return false;
    }
    string[lengthOfString] = symbol;
    return true;
}

/* If it's impossible to add, the function will return false. */
bool addOperatorToEndOfExpression(char* expression, char operator, int maxLengthOfExpression)
{
    bool isCorrectAdding = addToEndOfString(expression, operator, maxLengthOfExpression) &&
                           addToEndOfString(expression, ' ', maxLengthOfExpression);
    return isCorrectAdding;
}

/* indexOfDigit initially contains the index of the first digit of the rewritable number in infixExpression.
 * After the function works, indexOfDigit will contain the index of the last digit of the number.
 * If it's impossible to rewrite, the function will return false.
 * 'isNextOperator' checks the relative position of the operators and numbers in the infix expression. */
bool rewriteNumberToPostfixExpression(const char* infixExpression, char* postfixExpression, int* indexOfDigit,
                                      int maxLengthOfExpression, bool* isNextOperator)
{
    if (*isNextOperator)
    {
        return false;
    }
    *isNextOperator = true;

    bool isCorrectRewriting = true;
    char currentDigit = infixExpression[*indexOfDigit];
    do
    {
        isCorrectRewriting = addToEndOfString(postfixExpression, currentDigit, maxLengthOfExpression);
        if (!isCorrectRewriting)
        {
            return false;
        }

        (*indexOfDigit)++;
        currentDigit = infixExpression[*indexOfDigit];
    } while (isDigit(currentDigit));

    (*indexOfDigit)--;
    isCorrectRewriting = addToEndOfString(postfixExpression, ' ', maxLengthOfExpression);
    return isCorrectRewriting;
}

/* If it's impossible to push or the string is incorrect, the function will return false.
 * 'isNextOperator' checks the relative position of the operators and numbers in the infix expression. */
bool processOperatorWhenConvertingToPostfix(char* postfixExpression, StackOfChar* symbols, char operator,
                                            int maxLengthOfExpression, bool* isNextOperator)
{
    if (!(*isNextOperator))
    {
        return false;
    }
    *isNextOperator = false;

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

/* If it's impossible to push or the string is incorrect, the function will return false. */
bool processClosingBracketWhenConvertingToPostfix(char* postfixExpression, StackOfChar* symbols, int maxLengthOfExpression)
{
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

/* If it's impossible to push or the string is incorrect, the function will return false. */
bool pushRemainingOperators(char* postfixExpression, StackOfChar* symbols, int maxLengthOfExpression)
{
    char currentSymbol = '\0';
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

/* indexOfSymbol is an index of a symbol in infixExpression
 * If it's impossible to process or the string is incorrect, the function will return false.
 * 'isNextOperator' checks the relative position of the operators and numbers in the infix expression. */
bool processSymbolWhenConvertingToPostfix(char* infixExpression, char* postfixExpression, StackOfChar* symbols,
                                          int* indexOfSymbol, int capacityOfPostfixExpression, bool* isNextOperator)
{
    bool isCorrectExpression = true;
    char currentSymbol = infixExpression[*indexOfSymbol];

    if (isDigit(currentSymbol))
    {
        isCorrectExpression = rewriteNumberToPostfixExpression(infixExpression, postfixExpression, indexOfSymbol,
                                                               capacityOfPostfixExpression, isNextOperator);
    }
    else if (isOperator(currentSymbol))
    {
        isCorrectExpression = processOperatorWhenConvertingToPostfix(postfixExpression, symbols, currentSymbol,
                                                                     capacityOfPostfixExpression, isNextOperator);
    }
    else if (currentSymbol == ')')
    {
        isCorrectExpression = processClosingBracketWhenConvertingToPostfix(postfixExpression, symbols,
                                                                           capacityOfPostfixExpression);
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

/* If the input data is incorrect, the function will return false.
 * This function only processes the string of the infix expression
 * without pushing remaining operators to the postfix expression. */
bool processInfixExpressionWhenConverting(char* infixExpression, char* postfixExpression, StackOfChar* symbols,
                                          int capacityOfPostfixExpression)
{
    if (postfixExpression == NULL || infixExpression == NULL || symbols == NULL)
    {
        return false;
    }

    int lengthOfInfixExpression = strlen(infixExpression);

    bool isCorrectExpression = true;
    bool isNextOperator = false;
    for (int i = 0; i < lengthOfInfixExpression; i++)
    {
        isCorrectExpression = processSymbolWhenConvertingToPostfix(infixExpression, postfixExpression, symbols, &i,
                                                                   capacityOfPostfixExpression, &isNextOperator);
        if (!isCorrectExpression)
        {
            return false;
        }
    }
    return true;
}

bool convertInfixToPostfixNotation(char* infixExpression, char* postfixExpression, int capacityOfPostfixExpression)
{
    if (postfixExpression == NULL || infixExpression == NULL)
    {
        return false;
    }

    StackOfChar* symbols = createStackOfChar();
    bool isCorrectExpression = true;

    isCorrectExpression = processInfixExpressionWhenConverting(infixExpression, postfixExpression, symbols,
                                                               capacityOfPostfixExpression) &&
                          pushRemainingOperators(postfixExpression, symbols, capacityOfPostfixExpression);

    deleteStackOfChar(symbols);
    return isCorrectExpression;
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
bool processSymbolWhenCalculating(StackOfDouble* numbersInExpression, char checkingSymbol,
                                  char* postfixExpression, int* indexOfSymbol)
{
    if (isDigit(checkingSymbol))
    {
        int recordableNumber = 0;
        scanNumberFromString(&recordableNumber, postfixExpression, indexOfSymbol);
        pushToStackOfDouble(numbersInExpression, recordableNumber);
    }
    else if (checkingSymbol != ' ')
    {
        if (getStackOfDoubleSize(numbersInExpression) < 2 || !isOperator(checkingSymbol))
        {
            return false;
        }

        double secondNumberInOperation = popFromStackOfDouble(numbersInExpression);
        double firstNumberInOperation = popFromStackOfDouble(numbersInExpression);
        double resultOfOperation = 0.0;
        bool isDivisionByZero = false;
        isDivisionByZero = !performOperation(firstNumberInOperation, secondNumberInOperation, &resultOfOperation,
                                             checkingSymbol);
        if (isDivisionByZero)
        {
            return false;
        }
        pushToStackOfDouble(numbersInExpression, resultOfOperation);
    }
    return true;
}

/* If the expression is incorrect or (postfixExpression == NULL), the function will return false.
 * The result will be contained in the 'numbersInExpression'.
 * This function only processes the string of the postfix expression
 * without checking the calculating is correct. */
bool processPostfixExpressionWhenCalculating(char* postfixExpression, StackOfDouble* numbersInExpression)
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

bool isCorrectCompletionOfCalculating(StackOfDouble* numbersInExpression)
{
    return getStackOfDoubleSize(numbersInExpression) == 1;
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

    StackOfDouble* numbersInExpression = createStackOfDouble();

    bool isCorrectCalculating = processPostfixExpressionWhenCalculating(postfixExpression, numbersInExpression) &&
                                isCorrectCompletionOfCalculating(numbersInExpression);

    if (!isCorrectCalculating)
    {
        *resultOfExpression = 0;
    }
    else
    {
        *resultOfExpression = popFromStackOfDouble(numbersInExpression);
    }
    deleteStackOfDouble(numbersInExpression);
    return isCorrectCalculating;
}

bool calculateInfixExpression(char* infixExpression, double* resultOfExpression)
{
    int lengthOfInfixExpression = strlen(infixExpression);

    // The length of a postfix expression is not more than twice that an infix expression
    // (in an infix expression, spaces between operators and numbers may be absent, for example).
    int capacityOfPostfixExpression = (lengthOfInfixExpression + 1) * 2;
    char* postfixExpression = (char*) calloc(capacityOfPostfixExpression, sizeof(char));

    bool isCorrectCalculating = convertInfixToPostfixNotation(infixExpression, postfixExpression,
                                                              capacityOfPostfixExpression) &&
                                calculatePostfixExpression(postfixExpression, resultOfExpression);

    free(postfixExpression);
    return isCorrectCalculating;
}