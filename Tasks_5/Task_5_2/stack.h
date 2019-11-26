#pragma once

#include <stdbool.h>

typedef struct Stack Stack;
struct Stack;

Stack* createStack();

void pushToStack(Stack* stack, double value);

/* If the stack is empty, the function will return 0.0 */
double popFromStack(Stack* stack);

/* If the stack is empty, the function will return 0.0 */
double peekIntoStack(Stack* stack);

bool isStackEmpty(Stack* stack);

void deleteStack(Stack* stack);

int getStackSize(Stack* stack);
