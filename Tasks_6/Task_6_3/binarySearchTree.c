#include <stdlib.h>
#include <stdio.h>
#include "binarySearchTree.h"

typedef struct TreeElement TreeElement;
struct TreeElement
{
    int value;
    TreeElement* leftChild;
    TreeElement* rightChild;
};

struct BinarySearchTree
{
    TreeElement* root;
    int size;
};

TreeElement* createTreeElement(int value)
{
    TreeElement* newTreeElement = (TreeElement*) malloc(sizeof(TreeElement));
    newTreeElement->value = value;
    newTreeElement->rightChild = NULL;
    newTreeElement->leftChild = NULL;
    return newTreeElement;
}

bool isBinarySearchTreeEmpty(BinarySearchTree* tree)
{
    return tree == NULL || tree->root == NULL;
}

int getSizeOfBinaryTree(BinarySearchTree* tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    return tree->size;
}

BinarySearchTree* createBinarySearchTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}


TreeElement* getSubtreeWithInsertedElement(BinarySearchTree* tree, TreeElement* treeElement, int value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (treeElement == NULL)
    {
        TreeElement* newTreeElement = createTreeElement(value);
        tree->size++;
        return newTreeElement;
    }

    if (treeElement->value < value)
    {
        treeElement->rightChild = getSubtreeWithInsertedElement(tree, treeElement->rightChild, value);
    }
    else if (treeElement->value > value)
    {
        treeElement->leftChild = getSubtreeWithInsertedElement(tree, treeElement->leftChild, value);
    }
    return treeElement;
}

bool insertToBinarySearchTree(BinarySearchTree* tree, int value)
{
    if (tree == NULL)
    {
        return false;
    }
    tree->root = getSubtreeWithInsertedElement(tree, tree->root, value);
    return true;
}


bool isInSubtree(TreeElement* treeElement, int value)
{
    if (treeElement == NULL)
    {
        return false;
    }
    else if (treeElement->value < value)
    {
        return isInSubtree(treeElement->rightChild, value);
    }
    else if (treeElement->value > value)
    {
        return isInSubtree(treeElement->leftChild, value);
    }
    return true;
}

bool isInBinarySearchTree(BinarySearchTree* tree, int value)
{
    if (tree == NULL)
    {
        return false;
    }
    return isInSubtree(tree->root, value);
}


TreeElement* getMinimumInSubtree(TreeElement* treeElement)
{
    if (treeElement->leftChild != NULL)
    {
        return getMinimumInSubtree(treeElement->leftChild);
    }
    return treeElement;
}

// This function will directly remove the element to be deleted.
TreeElement* getElementReplacingDeletedOne(BinarySearchTree* tree, TreeElement* removableElement)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (removableElement->rightChild != NULL)
    {
        TreeElement* minInRightSubtree = getMinimumInSubtree(removableElement->rightChild);
        int value = minInRightSubtree->value;
        removeFromBinarySearchTree(tree, value);
        removableElement->value = value;
        return removableElement;
    }
    else
    {
        TreeElement* returnedElement = NULL;
        if (removableElement->leftChild != NULL)
        {
            returnedElement = removableElement->leftChild;
        }
        free(removableElement);
        tree->size--;
        return returnedElement;
    }
}

TreeElement* getSubtreeWithRemovedElement(BinarySearchTree* tree, TreeElement* treeElement, int value)
{
    if (tree == NULL || treeElement == NULL)
    {
        return NULL;
    }

    if (treeElement->value < value)
    {
        treeElement->rightChild = getSubtreeWithRemovedElement(tree, treeElement->rightChild, value);
    }
    else if (treeElement->value > value)
    {
        treeElement->leftChild = getSubtreeWithRemovedElement(tree, treeElement->leftChild, value);
    }
    else
    {
        return getElementReplacingDeletedOne(tree, treeElement);
    }
    return treeElement;
}

bool removeFromBinarySearchTree(BinarySearchTree* tree, int value)
{
    if (tree == NULL)
    {
        return false;
    }
    tree->root = getSubtreeWithRemovedElement(tree, tree->root, value);
    return true;
}


void traverseSubtreeInInfixOrder(TreeElement* treeElement, int array[], int* currentSize)
{
    if (treeElement == NULL || array == NULL)
    {
        return;
    }

    traverseSubtreeInInfixOrder(treeElement->leftChild, array, currentSize);
    array[*currentSize] = treeElement->value;
    (*currentSize)++;
    traverseSubtreeInInfixOrder(treeElement->rightChild, array, currentSize);
}

void traverseSubtreeInPostfixOrder(TreeElement* treeElement, int array[], int* currentSize)
{
    if (treeElement == NULL || array == NULL)
    {
        return;
    }

    traverseSubtreeInPostfixOrder(treeElement->leftChild, array, currentSize);
    traverseSubtreeInPostfixOrder(treeElement->rightChild, array, currentSize);
    array[*currentSize] = treeElement->value;
    (*currentSize)++;
}

void traverseSubtreeInPrefixOrder(TreeElement* treeElement, int array[], int* currentSize)
{
    if (treeElement == NULL || array == NULL)
    {
        return;
    }

    array[*currentSize] = treeElement->value;
    (*currentSize)++;
    traverseSubtreeInPrefixOrder(treeElement->leftChild, array, currentSize);
    traverseSubtreeInPrefixOrder(treeElement->rightChild, array, currentSize);
}

int* traverseBinarySearchTree(BinarySearchTree* tree, Traverse kindOfTraverse)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int* array = (int*) malloc(tree->size * sizeof(int));
    int currentSize = 0;

    switch (kindOfTraverse)
    {
        case prefixTraverse:
        {
            traverseSubtreeInPrefixOrder(tree->root, array, &currentSize);
            break;
        }

        case infixTraverse:
        {
            traverseSubtreeInInfixOrder(tree->root, array, &currentSize);
            break;
        }

        case postfixTraverse:
        {
            traverseSubtreeInPostfixOrder(tree->root, array, &currentSize);
            break;
        }

        default:
        {
            break;
        }
    }

    return array;
}


void deleteSubtree(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return;
    }

    deleteSubtree(treeElement->leftChild);
    deleteSubtree(treeElement->rightChild);
    free(treeElement);
}

void deleteBinarySearchTree(BinarySearchTree* tree)
{
    if (tree != NULL)
    {
        deleteSubtree(tree->root);
    }
    free(tree);
}

void printSubtree(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        printf("null");
        return;
    }

    printf("(%d ", treeElement->value);
    printSubtree(treeElement->leftChild);
    printf(" ");
    printSubtree(treeElement->rightChild);
    printf(")");
}

bool printBinarySearchTree(BinarySearchTree* tree)
{
    if (tree == NULL)
    {
        return false;
    }
    printSubtree(tree->root);
    return true;
}