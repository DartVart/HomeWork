#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

typedef struct ListElement ListElement;
struct ListElement
{
    int value;
    ListElement* next;
};

struct List
{
    ListElement* first;
    int size;
};

ListElement* createListElement(int value)
{
    ListElement* newElement = (ListElement*) malloc(sizeof(ListElement));
    newElement->value = value;
    newElement->next = NULL;
    return newElement;
}

List* createList()
{
    List* list = (List*) malloc(sizeof(List));
    list->first = NULL;
    list->size = 0;
    return list;
}

bool isListEmpty(List* list)
{
    return list == NULL || list->first == NULL;
}

/* If the list is empty or the index is incorrect, the function will return NULL. */
ListElement* getElement(List* list, int index)
{
    if (isListEmpty(list) || index >= list->size || index < 0)
    {
        return NULL;
    }

    ListElement* returnElement = list->first;

    for (int i = 0; i < index; i++)
    {
        returnElement = returnElement->next;
    }
    return returnElement;
}

void insertionSort(List* list)
{

    ListElement* newRoot = NULL;
    ListElement* currentRoot = list->first;

    while (currentRoot != NULL)
    {
        ListElement* nodalElement = currentRoot;
        currentRoot = currentRoot->next;

        if (newRoot == NULL || nodalElement->value < newRoot->value)
        {
            nodalElement->next = newRoot;
            newRoot = nodalElement;
        }
        else
        {
            ListElement* currentElement = newRoot;
            while (currentElement->next != NULL && nodalElement->value >= currentElement->next->value)
            {
                currentElement = currentElement->next;
            }

            nodalElement->next = currentElement->next;
            currentElement->next = nodalElement;
        }
    }

    list->first = newRoot;
}

bool insertToList(List* list, int value, int index)
{
    if (list == NULL || index > list->size || index < 0)
    {
        return false;
    }

    ListElement* newElement = createListElement(value);

    if (list->first == NULL)
    {
        list->first = newElement;
    }
    else if (index == 0)
    {
        newElement->next = list->first;
        list->first = newElement;
    }
    else
    {
        ListElement* tempElement = getElement(list, index - 1);
        newElement->next = tempElement->next;
        tempElement->next = newElement;
    }

    list->size++;
    return true;
}

bool deleteFromList(List* list, int index)
{
    if (isListEmpty(list) || index >= list->size || index < 0)
    {
        return false;
    }

    ListElement* deletedElement = NULL;
    if (index == 0)
    {
        deletedElement = list->first;
        list->first = deletedElement->next;
    }
    else
    {
        ListElement* tempElement = getElement(list, index - 1);
        deletedElement = tempElement->next;
        tempElement->next = deletedElement->next;
    }

    free(deletedElement);
    list->size--;
    return true;
}

int locateOfListElement(List* list, int value)
{
    if (list == NULL)
    {
        return -2;
    }

    int returnIndex = 0;
    ListElement* tempElement = list->first;
    while (tempElement != NULL)
    {
        if (tempElement->value == value)
        {
            return returnIndex;
        }
        returnIndex++;
        tempElement = tempElement->next;
    }

    return -1;
}

int retrieveValueFromList(List* list, int index)
{
    if (isListEmpty(list) || index >= list->size || index < 0)
    {
        return 0;
    }
    ListElement* returnedElement = getElement(list, index);
    return returnedElement->value;
}

int getListSize(List* list)
{
    if (list == NULL)
    {
        return -1;
    }
    return list->size;
}

void deleteList(List* list)
{
    ListElement* tempElement = list->first;
    ListElement* deletedElement = NULL;

    while (tempElement != NULL)
    {
        deletedElement = tempElement;
        tempElement = tempElement->next;
        free(deletedElement);
    }

    free(list);
}


void printList(List* list)
{
    if (isListEmpty(list))
    {
        printf("List is empty.");
    }
    ListElement* printedElement = list->first;
    while (printedElement != NULL)
    {
        printf("%d ", printedElement->value);
        printedElement = printedElement->next;
    }
}
