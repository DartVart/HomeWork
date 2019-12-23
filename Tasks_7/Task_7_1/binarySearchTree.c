#include <stdlib.h>
#include <stdio.h>
#include "binarySearchTree.h"

typedef struct TreeElement TreeElement;
struct TreeElement
{
    int value;
    int height;
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
    newTreeElement->height = 1;
    newTreeElement->rightChild = NULL;
    newTreeElement->leftChild = NULL;
    return newTreeElement;
}

BinarySearchTree* createBinarySearchTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}


int getHeight(TreeElement* treeElement)
{
    return treeElement != NULL ? treeElement->height : 0;
}

/* If (treeElement == NULL), the function will return 0. */
int getBalanceFactor(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return 0;
    }
    return getHeight(treeElement->rightChild) - getHeight(treeElement->leftChild);
}

int getMaximum(int a, int b)
{
    return a > b ? a : b;
}

/* If (treeElement == NULL), the function will return false. */
bool updateHeight(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return false;
    }
    int heightOfRightChild = getHeight(treeElement->rightChild);
    int heightOfLeftChild = getHeight(treeElement->leftChild);
    treeElement->height = getMaximum(heightOfLeftChild, heightOfRightChild) + 1;
    return true;
}

TreeElement* rotateRight(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return NULL;
    }

    TreeElement* pivot = treeElement->leftChild;
    treeElement->leftChild = pivot->rightChild;
    pivot->rightChild = treeElement;
    updateHeight(treeElement);
    updateHeight(pivot);

    return pivot;
}

TreeElement* rotateLeft(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return NULL;
    }

    TreeElement* pivot = treeElement->rightChild;
    treeElement->rightChild = pivot->leftChild;
    pivot->leftChild = treeElement;
    updateHeight(treeElement);
    updateHeight(pivot);

    return pivot;
}

TreeElement* balanceTreeElement(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return NULL;
    }

    updateHeight(treeElement);

    int balanceFactor = getBalanceFactor(treeElement);

    if (balanceFactor == 2)
    {
        if (getBalanceFactor(treeElement->rightChild) < 0)
        {
            treeElement->rightChild = rotateRight(treeElement->rightChild);
        }
        return rotateLeft(treeElement);
    }
    if (balanceFactor == -2)
    {
        if (getBalanceFactor(treeElement->leftChild) > 0)
        {
            treeElement->leftChild = rotateLeft(treeElement->leftChild);
        }
        return rotateRight(treeElement);
    }

    return treeElement;
}


bool isBinarySearchTreeEmpty(BinarySearchTree* tree)
{
    return tree == NULL || tree->root == NULL;
}

int getSizeOfBinaryTree(BinarySearchTree* tree)
{
    return tree != NULL ? tree->size : -1;
}


TreeElement* getSubtreeWithInsertedElement(BinarySearchTree* tree, TreeElement* treeElement, int value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (treeElement == NULL)
    {
        tree->size++;
        return createTreeElement(value);
    }

    if (treeElement->value < value)
    {
        treeElement->rightChild = getSubtreeWithInsertedElement(tree, treeElement->rightChild, value);
    }
    else if (treeElement->value > value)
    {
        treeElement->leftChild = getSubtreeWithInsertedElement(tree, treeElement->leftChild, value);
    }
    return balanceTreeElement(treeElement);
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

/* This function removes the minimum element from the subtree, but doesn't free memory for it. */
TreeElement* separateMinimumFromSubtree(TreeElement* treeElement)
{
    if (treeElement == NULL)
    {
        return NULL;
    }

    if (treeElement->leftChild == NULL)
    {
        return treeElement->rightChild;
    }
    treeElement->leftChild = separateMinimumFromSubtree(treeElement->leftChild);
    return balanceTreeElement(treeElement);
}

/* This function will directly remove the element to be deleted. */
TreeElement* getElementReplacingDeletedOne(BinarySearchTree* tree, TreeElement* removableElement)
{
    if (tree == NULL)
    {
        return NULL;
    }

    TreeElement* rightChild = removableElement->rightChild;
    TreeElement* leftChild = removableElement->leftChild;
    free(removableElement);
    tree->size--;

    if (rightChild == NULL)
    {
        return leftChild;
    }

    TreeElement* minimumInRightSubtree = getMinimumInSubtree(rightChild);
    minimumInRightSubtree->rightChild = separateMinimumFromSubtree(rightChild);
    minimumInRightSubtree->leftChild = leftChild;

    return balanceTreeElement(minimumInRightSubtree);
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
    return balanceTreeElement(treeElement);
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


void traverseSubtreeInInfixOrder(TreeElement* treeElement, int* array, int* currentSize)
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

void traverseSubtreeInPostfixOrder(TreeElement* treeElement, int* array, int* currentSize)
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

void traverseSubtreeInPrefixOrder(TreeElement* treeElement, int* array, int* currentSize)
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
    int sizeOfArray = 0;

    switch (kindOfTraverse)
    {
        case prefixTraverse:
        {
            traverseSubtreeInPrefixOrder(tree->root, array, &sizeOfArray);
            break;
        }

        case infixTraverse:
        {
            traverseSubtreeInInfixOrder(tree->root, array, &sizeOfArray);
            break;
        }

        case postfixTraverse:
        {
            traverseSubtreeInPostfixOrder(tree->root, array, &sizeOfArray);
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