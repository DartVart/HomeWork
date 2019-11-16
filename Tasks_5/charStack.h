#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdbool.h>

typedef struct Stack Stack;
struct Stack;

Stack* createStack();

void pushToStack(Stack* stack, char value);

/* If the stack is empty, the function will return '\000' */
char popFromStack(Stack* stack);

/* If the stack is empty, the function will return '\000' */
char peekIntoStack(Stack* stack);

bool isStackEmpty(Stack* stack);

void deleteStack(Stack* stack);

int getStackSize(Stack* stack);

#endif //CHAR_STACK_H
