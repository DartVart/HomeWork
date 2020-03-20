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
    return set == NULL || isBinarySearchTreeEmpty(set->tree);
}

bool insertToSet(Set* set, int value)
{
    return set != NULL && insertToBinarySearchTree(set->tree, value);
}

bool removeFromSet(Set* set, int value)
{
    return set != NULL && removeFromBinarySearchTree(set->tree, value);
}

bool isInSet(Set* set, int value)
{
    return set != NULL && isInBinarySearchTree(set->tree, value);
}

int* getSetInAscendingOrder(Set* set)
{
    if (set == NULL)
    {
        return NULL;
    }
    return traverseBinarySearchTree(set->tree, infixTraverse);
}

bool printSetAsTree(Set* set)
{
    return set != NULL && printBinarySearchTree(set->tree);
}

int getSizeOfSet(Set* set)
{
    if (set == NULL)
    {
        return -1;
    }
    return getSizeOfBinaryTree(set->tree);
}

void deleteSet(Set* set)
{
    if (set == NULL)
    {
        return;
    }
    deleteBinarySearchTree(set->tree);
    free(set);
}