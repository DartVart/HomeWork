#include <stdlib.h>
#include "stackOfDouble.h"

typedef struct StackOfDoubleElement StackOfDoubleElement;
struct StackOfDoubleElement
{
    double value;
    StackOfDoubleElement* next;
};

struct StackOfDouble
{
    StackOfDoubleElement* top;
    int size;
};

StackOfDouble* createStackOfDouble()
{
    StackOfDouble* stack = (StackOfDouble*) malloc(sizeof(StackOfDouble));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

StackOfDoubleElement* createStackOfDoubleElement(double value, StackOfDoubleElement* nextElement)
{
    StackOfDoubleElement* stackElement = (StackOfDoubleElement*) malloc(sizeof(StackOfDoubleElement));
    stackElement->value = value;
    stackElement->next = nextElement;
    return stackElement;
}

bool pushToStackOfDouble(StackOfDouble* stack, double value)
{
    if (stack == NULL)
    {
        return false;
    }

    StackOfDoubleElement* newElement = createStackOfDoubleElement(value, stack->top);
    stack->top = newElement;
    stack->size++;

    return true;
}

double popFromStackOfDouble(StackOfDouble* stack)
{
    if (isStackOfDoubleEmpty(stack))
    {
        return 0.0;
    }

    StackOfDoubleElement* poppedElement = stack->top;
    double returnValue = poppedElement->value;
    stack->top = poppedElement->next;
    free(poppedElement);
    stack->size--;

    return returnValue;
}

double peekIntoStackOfDouble(StackOfDouble* stack)
{
    if (isStackOfDoubleEmpty(stack))
    {
        return 0.0;
    }

    return stack->top->value;
}

bool isStackOfDoubleEmpty(StackOfDouble* stack)
{
    return stack == NULL || stack->top == NULL;
}

void deleteStackOfDouble(StackOfDouble* stack)
{
    while (!isStackOfDoubleEmpty(stack))
    {
        popFromStackOfDouble(stack);
    }

    free(stack);
}

int getStackOfDoubleSize(StackOfDouble* stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    return stack->size;
}
