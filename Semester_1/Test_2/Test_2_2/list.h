#pragma once

#include <stdbool.h>

typedef struct List List;
struct List;

List* createList();

bool isListEmpty(List* list);

/* If (list == NULL) or the index is incorrect, the function will return false. */
bool insertToList(List *list, int value, int index);

/* If the list is empty or the index is incorrect, the function will return false. */
bool deleteFromList(List* list, int index);

/* If (list == NULL), the function will return -2;
 * If the element isn't found, it will return -1. */
int locateOfListElement(List *list, int value);

/* If the list is empty or the index is incorrect, the function will return 0. */
int retrieveValueFromList(List* list, int index);

/* If (list == NULL), the function will return false. */
int getListSize(List* list);

void deleteList(List* list);

void insertionSort(List* list);

void printList(List* list);
