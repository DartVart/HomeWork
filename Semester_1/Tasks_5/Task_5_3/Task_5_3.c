#include <stdio.h>
#include <stdlib.h>
#include "notationOfExpression.h"
#include "stringReading.h"

int main()
{
    printf("Enter an expression in infix notation:\n");
    char* infixExpression = getStringFromStream(stdin, readingWithSpaces);

    double resultOfExpression = 0;
    bool isExpressionCorrect = calculateInfixExpression(infixExpression, &resultOfExpression);

    if (isExpressionCorrect)
    {
        printf("Result of the expression: %lf", resultOfExpression);
    }
    else
    {
        printf("You entered an incorrect expression!");
    }

    free(infixExpression);
    return 0;
}