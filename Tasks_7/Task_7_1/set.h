/**
 * This is beta of a module that implements the set. Debugging may be required (as of December 20, 2019)
 **/

#pragma once

#include <stdbool.h>

typedef struct Set Set;
struct Set;

Set* createSet();

/* If (set == NULL), the function will return false. */
bool insertToSet(Set* set, int value);

bool isSetEmpty(Set* set);

/* If (set == NULL), the function will return false. */
bool removeFromSet(Set* set, int value);

bool isInSet(Set* set, int value);

/* The function returns an array of integers belonging to the set in the ascending order.
 * If (set == NULL), the function will return NULL. */
int* getSetInAscendingOrder(Set* set);

/* This function is only needed during beta testing.
 * Since the set is implemented as a binary search tree, it can be displayed in the console
 * in the form: (node (left subtree) (right subtree)).
 * If (set == NULL), the function will return false. */
bool printSetAsTree(Set* set);

/* If (set == NULL), the function will return -1. */
int getSizeOfSet(Set* set);

void deleteSet(Set* set);