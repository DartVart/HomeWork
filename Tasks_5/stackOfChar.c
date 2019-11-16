#include <stdlib.h>
#include "stackOfChar.h"

typedef struct StackElement StackElement;
struct StackElement
{
    char value;
    StackElement* next;
};

struct Stack
{
    StackElement* top;
    int size;
};

Stack* createStack()
{
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

StackElement* createStackElement(char value, StackElement* nextElement)
{
    StackElement* stackElement = (StackElement*) malloc(sizeof(StackElement));
    stackElement->value = value;
    stackElement->next = nextElement;
    return stackElement;
}

void pushToStack(Stack* stack, char value)
{
    StackElement* newElement = createStackElement(value, stack->top);
    stack->top = newElement;
    stack->size++;
}

char popFromStack(Stack* stack)
{
    if (isStackEmpty(stack))
    {
        return '\000';
    }

    StackElement* poppedElement = stack->top;
    char returnValue = poppedElement->value;
    stack->top = poppedElement->next;
    free(poppedElement);
    stack->size--;

    return returnValue;
}

char peekIntoStack(Stack* stack)
{
    if (isStackEmpty(stack))
    {
        return '\000';
    }

    return stack->top->value;
}

bool isStackEmpty(Stack* stack)
{
    return stack->top == 0;
}

void deleteStack(Stack* stack)
{
    while (!isStackEmpty(stack))
    {
        popFromStack(stack);
    }

    free(stack);
}

int getStackSize(Stack* stack)
{
    return stack->size;
}
