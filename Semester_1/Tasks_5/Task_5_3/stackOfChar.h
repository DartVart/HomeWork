#pragma once

#include <stdbool.h>

typedef struct StackOfChar StackOfChar;
struct StackOfChar;

StackOfChar* createStackOfChar();

/* If (stack == NULL), the function will return false */
bool pushToStackOfChar(StackOfChar* stack, char value);

/* If the stack is empty or (stack == NULL), the function will return '\0' */
char popFromStackOfChar(StackOfChar* stack);

/* If the stack is empty or (stack == NULL), the function will return '\0' */
char peekIntoStackOfChar(StackOfChar* stack);

bool isStackOfCharEmpty(StackOfChar* stack);

void deleteStackOfChar(StackOfChar* stack);

/* If (stack == NULL), the function will return -1 */
int getStackOfCharSize(StackOfChar* stack);