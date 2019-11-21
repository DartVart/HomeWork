#include <stdlib.h>
#include "circularList.h"

typedef struct CircularListElement CircularListElement;
struct CircularListElement
{
    int value;
    CircularListElement* next;
};

struct CircularList
{
    CircularListElement* lastAddedElement;
    CircularListElement* beforeLastDeletedElement;
    int size;
};

CircularList* createCircularList()
{
    CircularList* circularList = (CircularList*) malloc(sizeof(CircularList));
    circularList->size = 0;
    circularList->lastAddedElement = NULL;
    circularList->beforeLastDeletedElement = NULL;
    return circularList;
}

bool isCircularListEmpty(CircularList* circularList)
{
    return circularList->size == 0;
}

void addToCircularList(CircularList* circularList, int value)
{
    CircularListElement* newElement = (CircularListElement*) malloc(sizeof(CircularListElement));
    newElement->value = value;

    if (isCircularListEmpty(circularList))
    {
        circularList->lastAddedElement = newElement;
        newElement->next = newElement;
    }
    else
    {
        newElement->next = circularList->lastAddedElement->next;
        circularList->lastAddedElement->next = newElement;
        circularList->lastAddedElement = newElement;
    }

    circularList->size++;
}

int deleteElementOfCircularList(CircularList* circularList, int position, StartPositionToDelete startPosition)
{
    int returnedValue = 0;

    if (isCircularListEmpty(circularList))
    {
        return 0;
    }

    if (startPosition == FIRST || circularList->beforeLastDeletedElement == NULL)
    {
        circularList->beforeLastDeletedElement = circularList->lastAddedElement;
    }

    for (int i = 0; i < position; i++)
    {
        circularList->beforeLastDeletedElement = circularList->beforeLastDeletedElement->next;
    }

    CircularListElement* temp = circularList->beforeLastDeletedElement->next;
    if (circularList->lastAddedElement == temp)
    {
        circularList->lastAddedElement = circularList->beforeLastDeletedElement;
    }

    if (circularList->size == 1)
    {
        circularList->lastAddedElement = NULL;
        circularList->beforeLastDeletedElement = NULL;
    }
    else
    {
        circularList->beforeLastDeletedElement->next = temp->next;
    }

    returnedValue = temp->value;

    free(temp);

    circularList->size--;

    return returnedValue;
}

int getCircularListSize(CircularList* circularList)
{
    return circularList->size;
}

void deleteCircularList(CircularList* circularList)
{
    if (!isCircularListEmpty(circularList))
    {
        CircularListElement *afterDeletedElement = circularList->lastAddedElement->next;
        CircularListElement *deletedElement = NULL;

        for (int i = 0; i < circularList->size; i++)
        {
            deletedElement = afterDeletedElement;
            afterDeletedElement = deletedElement->next;
            free(deletedElement);
        }
    }

    free(circularList);
}
