#pragma once

#include <stdbool.h>

typedef struct StackOfDouble StackOfDouble;
struct StackOfDouble;

StackOfDouble* createStackOfDouble();

void pushToStackOfDouble(StackOfDouble* stack, double value);

/* If the stack is empty, the function will return 0.0 */
double popFromStackOfDouble(StackOfDouble* stack);

/* If the stack is empty, the function will return 0.0 */
double peekIntoStackOfDouble(StackOfDouble* stack);

bool isStackOfDoubleEmpty(StackOfDouble* stack);

void deleteStackOfDouble(StackOfDouble* stack);

int getStackOfDoubleSize(StackOfDouble* stack);