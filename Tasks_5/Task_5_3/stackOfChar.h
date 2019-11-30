#pragma once

#include <stdbool.h>

typedef struct StackOfChar StackOfChar;
struct StackOfChar;

StackOfChar* createStackOfChar();

void pushToStackOfChar(StackOfChar* stack, char value);

/* If the stack is empty, the function will return '\000' */
char popFromStackOfChar(StackOfChar* stack);

/* If the stack is empty, the function will return '\000' */
char peekIntoStackOfChar(StackOfChar* stack);

bool isStackOfCharEmpty(StackOfChar* stack);

void deleteStackOfChar(StackOfChar* stack);

int getStackOfCharSize(StackOfChar* stack);