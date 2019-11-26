#pragma once

#include <stdbool.h>

typedef struct Stack Stack;
struct Stack;

Stack* createStack();

/* If (stack == NULL), the function will return false */
bool pushToStack(Stack* stack, double value);

/* If the stack is empty or (stack == NULL), the function will return 0.0 */
double popFromStack(Stack* stack);

/* If the stack is empty or (stack == NULL), the function will return 0.0 */
double peekIntoStack(Stack* stack);

bool isStackEmpty(Stack* stack);

void deleteStack(Stack* stack);

/* If (stack == NULL), the function will return -1 */
int getStackSize(Stack* stack);