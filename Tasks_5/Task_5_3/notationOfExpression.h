/**
 * This module implements actions with various notations of mathematical expressions.
 * Expressions are represented as a char array.
 *
 * As of December 1, 2019, this module doesn't implement all actions with notations of mathematical expressions.
 */
#pragma once

#include "stdbool.h"

extern const int maxSizeOfExpression;

/* The result will be written into resultOfExpression.
 * If the expression is incorrect, the function will return false and
 * the value of resultOfExpression will be 0.0 */
bool calculatePostfixExpression(char* postfixExpression, double* resultOfExpression);

/* This function doesn't detect all incorrect expressions, but if it does, it will return false. */
bool convertInfixToPostfixNotation(char infixExpression[], char postfixExpression[]);