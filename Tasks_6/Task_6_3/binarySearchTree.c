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
    return tree->root == NULL;
}

int getSizeOfBinaryTree(BinarySearchTree* tree)
{
    return tree->size;
}

BinarySearchTree* createBinarySearchTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}

void insertToBinarySearchTree(BinarySearchTree* tree, int value)
{
    TreeElement* newTreeElement = createTreeElement(value);

    if (isBinarySearchTreeEmpty(tree))
    {
        tree->root = newTreeElement;
    }
    else
    {
        TreeElement* currentElement = tree->root;

        while (true)
        {
            if (newTreeElement->value < currentElement->value)
            {
                if (currentElement->leftChild == NULL)
                {
                    currentElement->leftChild = newTreeElement;
                    break;
                }
                else
                {
                    currentElement = currentElement->leftChild;
                }
            }
            else if (newTreeElement->value > currentElement->value)
            {
                if (currentElement->rightChild == NULL)
                {
                    currentElement->rightChild = newTreeElement;
                    break;
                }
                else
                {
                    currentElement = currentElement->rightChild;
                }
            }
            else
            {
                return;
            }
        }
    }

    tree->size++;
}

bool isInBinarySearchTree(BinarySearchTree* tree, int value)
{
    TreeElement* current = tree->root;

    while (true)
    {
        if (current == NULL)
        {
            return false;
        }
        else if (current->value < value)
        {
            current = current->rightChild;
        }
        else if (current->value > value)
        {
            current = current->leftChild;
        }
        else
        {
            return true;
        }
    }
}

/* If you need to remove the root, then it's necessary that
 * parentOfRemovedElement must have value NULL and newChild must point to root. */
void linkElementsAfterRemove(BinarySearchTree* tree, TreeElement* parentOfRemovedElement,
                             TreeElement* newChild, bool isLeftChild)
{
    if (parentOfRemovedElement == NULL)
    {
        tree->root = newChild;
    }
    else
    {
        if (isLeftChild)
        {
            parentOfRemovedElement->leftChild = newChild;
        }
        else
        {
            parentOfRemovedElement->rightChild = newChild;
        }
    }
}

bool removeFromBinarySearchTree(BinarySearchTree* tree, int value)
{
    if (tree->root == NULL)
    {
        return false;
    }

    TreeElement* parentOfRemovedElement = NULL;
    TreeElement* removableElement = tree->root;
    bool isLeftChild = false;

    while (removableElement->value != value)
    {
        parentOfRemovedElement = removableElement;

        if (removableElement->value > value)
        {
            removableElement = removableElement->leftChild;
            isLeftChild = true;
        }
        else
        {
            removableElement = removableElement->rightChild;
            isLeftChild = false;
        }

        if (removableElement == NULL)
        {
            return false;
        }
    }

    if (removableElement->rightChild == NULL &&
        removableElement->leftChild == NULL)
    {
        linkElementsAfterRemove(tree, parentOfRemovedElement, NULL, isLeftChild);
    }
    else if (removableElement->rightChild != NULL &&
             removableElement->leftChild != NULL)
    {
        TreeElement* smallestRightChild = removableElement->rightChild;

        while (smallestRightChild->leftChild != NULL)
        {
            smallestRightChild = smallestRightChild->leftChild;
        }

        int valueOfReplacingElement = smallestRightChild->value;
        removeFromBinarySearchTree(tree, smallestRightChild->value);
        removableElement->value = valueOfReplacingElement;
        tree->size--;
        return true;
    }
    else if (removableElement->leftChild != NULL)
    {
        linkElementsAfterRemove(tree, parentOfRemovedElement, removableElement->leftChild, isLeftChild);
    }
    else
    {
        linkElementsAfterRemove(tree, parentOfRemovedElement, removableElement->rightChild, isLeftChild);
    }

    free(removableElement);
    tree->size--;
    return true;
}

void traverseSubtreeInInfixOrder(TreeElement* treeElement, int array[], int* currentSize)
{
    if (treeElement == NULL)
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
    if (treeElement == NULL)
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
    if (treeElement == NULL)
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
    int* array = (int*) malloc(tree->size * sizeof(int));
    int currentSize = 0;

    switch (kindOfTraverse)
    {
        case PREFIX_TRAVERSE:
        {
            traverseSubtreeInPrefixOrder(tree->root, array, &currentSize);
            break;
        }

        case INFIX_TRAVERSE:
        {
            traverseSubtreeInInfixOrder(tree->root, array, &currentSize);
            break;
        }

        case POSTFIX_TRAVERSE:
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
    deleteSubtree(tree->root);
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

void printBinarySearchTree(BinarySearchTree* tree)
{
    printSubtree(tree->root);
}
