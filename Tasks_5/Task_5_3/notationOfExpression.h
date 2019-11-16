/**
 * This module implements actions with various notations of mathematical expressions.
 * Expressions are represented as a char array.
 *
 * As of November 16, 2019, this module doesn't implement all actions with notations of mathematical expressions.
 */

#ifndef NOTATIONOFEXPRESSION_H
#define NOTATIONOFEXPRESSION_H

#include "stdbool.h"

#define maxSizeOfExpression 1000

/* The result will be written into resultOfExpression.
 * If the expression is incorrect, the function will return false and
 * the value of resultOfExpression will be 0.0 */
bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression);

/* This function doesn't detect all incorrect expressions, but if it does, it will return false. */
bool convertInfixToPostfixNotation(char infixExpression[], char postfixExpression[]);

#endif //NOTATIONOFEXPRESSION_H
