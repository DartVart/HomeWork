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

void pushToStackOfChar(StackOfChar* stack, char value)
{
    StackOfCharElement* newElement = createStackOfCharElement(value, stack->top);
    stack->top = newElement;
    stack->size++;
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
    return stack->top == 0;
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
    return stack->size;
}
