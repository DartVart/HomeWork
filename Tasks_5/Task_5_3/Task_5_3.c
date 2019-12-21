#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notationOfExpression.h"
#include "stringReading.h"

int main()
{
    printf("Enter an expression in infix notation:");
    char* infixExpression = getStringFromStream(stdin, readingWithSpaces);
    int lengthOfExpression = strlen(infixExpression) * 2;
    char* postfixExpression = (char*) calloc(lengthOfExpression, sizeof(char));

    double resultOfExpression = 0.0;
    bool isExpressionCorrect = convertInfixToPostfixNotation(infixExpression, postfixExpression, lengthOfExpression);
    if (isExpressionCorrect)
    {
        isExpressionCorrect = calculatePostfixExpression(postfixExpression, &resultOfExpression);
    }

    if (isExpressionCorrect)
    {
        printf("%s = %lf", infixExpression, resultOfExpression);
    }
    else
    {
        printf("You entered an incorrect expression!");
    }

    free(infixExpression);
    free(postfixExpression);
    return 0;
}