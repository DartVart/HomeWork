#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <stdbool.h>

typedef struct CircularList CircularList;
struct CircularList;

typedef enum StartPositionToDelete StartPositionToDelete;
enum StartPositionToDelete
{
    FIRST,
    AFTER_LAST_DELETED
};

CircularList* createCircularList();

/* The new element will follow the last element added. */
void addToCircularList(CircularList* circularList, int value);

/* The position of the element to be deleted can be counted either from the first element
 * ((startPosition == FIRST) or (startPosition == AFTER_LAST_DELETED and there was no deletion before))
 * or from the element following the last deleted element (startPosition == AFTER_LAST_DELETED).
 * Position is counted from 0.*/
int deleteElementOfCircularList(CircularList* circularList, int position, enum StartPositionToDelete startPosition);

bool isCircularListEmpty(CircularList* circularList);

int getCircularListSize(CircularList* circularList);

void deleteCircularList(CircularList* circularList);

#endif //CIRCULARLIST_H
