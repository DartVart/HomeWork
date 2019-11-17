#include <stdlib.h>
#include "binarySearchTree.h"
#include "set.h"

struct Set
{
    BinarySearchTree* tree;
};

Set* createSet()
{
    Set* newSet = (Set*) malloc(sizeof(Set));
    newSet->tree = createBinarySearchTree();
    return newSet;
}

bool isSetEmpty(Set* set)
{
    return isBinarySearchTreeEmpty(set->tree);
}

void insertToSet(Set* set, int value)
{
    insertToBinarySearchTree(set->tree, value);
}

bool removeFromSet(Set* set, int value)
{
    return removeFromBinarySearchTree(set->tree, value);
}

bool isInSet(Set* set, int value)
{
    return isInBinarySearchTree(set->tree, value);
}

int* getSetInAscendingOrder(Set* set)
{
   return traverseBinarySearchTree(set->tree, INFIX_TRAVERSE);
}

void printSet(Set* set)
{
    printBinarySearchTree(set->tree);
}

int getSizeOfSet(Set* set)
{
    return getSizeOfBinaryTree(set->tree);
}

void deleteSet(Set* set)
{
    deleteBinarySearchTree(set->tree);
}
