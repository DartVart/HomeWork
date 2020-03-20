#pragma once

#include <stdbool.h>

typedef struct StackOfDouble StackOfDouble;
struct StackOfDouble;

StackOfDouble* createStackOfDouble();

/* If (stack == NULL), the function will return false */
bool pushToStackOfDouble(StackOfDouble* stack, double value);

/* If the stack is empty or (stack == NULL), the function will return 0.0 */
double popFromStackOfDouble(StackOfDouble* stack);

/* If the stack is empty or (stack == NULL), the function will return 0.0 */
double peekIntoStackOfDouble(StackOfDouble* stack);

bool isStackOfDoubleEmpty(StackOfDouble* stack);

void deleteStackOfDouble(StackOfDouble* stack);

/* If (stack == NULL), the function will return -1 */
int getStackOfDoubleSize(StackOfDouble* stack);