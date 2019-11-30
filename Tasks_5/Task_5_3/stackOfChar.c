#include <stdlib.h>
#include "stackOfChar.h"

typedef struct StackOfCharElement StackOfCharElement;
struct StackOfCharElement
{
    char value;
    StackOfCharElement* next;
};

struct StackOfChar
{
    StackOfCharElement* top;
    int size;
};

StackOfChar* createStackOfChar()
{
    StackOfChar* stack = (StackOfChar*) malloc(sizeof(StackOfChar));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

StackOfCharElement* createStackOfCharElement(char value, StackOfCharElement* nextElement)
{
    StackOfCharElement* stackElement = (StackOfCharElement*) malloc(sizeof(StackOfCharElement));
    stackElement->value = value;
    stackElement->next = nextElement;
    return stackElement;
}

bool pushToStackOfChar(StackOfChar* stack, char value)
{
    if (stack == NULL)
    {
        return false;
    }

    StackOfCharElement* newElement = createStackOfCharElement(value, stack->top);
    stack->top = newElement;
    stack->size++;

    return true;
}

char popFromStackOfChar(StackOfChar* stack)
{
    if (isStackOfCharEmpty(stack))
    {
        return '\000';
    }

    StackOfCharElement* poppedElement = stack->top;
    char returnValue = poppedElement->value;
    stack->top = poppedElement->next;
    free(poppedElement);
    stack->size--;

    return returnValue;
}

char peekIntoStackOfChar(StackOfChar* stack)
{
    if (isStackOfCharEmpty(stack))
    {
        return '\000';
    }

    return stack->top->value;
}

bool isStackOfCharEmpty(StackOfChar* stack)
{
    return stack == NULL || stack->top == NULL;
}

void deleteStackOfChar(StackOfChar* stack)
{
    while (!isStackOfCharEmpty(stack))
    {
        popFromStackOfChar(stack);
    }

    free(stack);
}

int getStackOfCharSize(StackOfChar* stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    return stack->size;
}
