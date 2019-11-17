/**
 * This module implements an unbalanced binary search tree.
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;
struct BinarySearchTree;

typedef enum Traverse Traverse;
enum Traverse
{
    PREFIX_TRAVERSE,
    INFIX_TRAVERSE,
    POSTFIX_TRAVERSE
};

BinarySearchTree* createBinarySearchTree();

void insertToBinarySearchTree(BinarySearchTree* tree, int value);

bool isInBinarySearchTree(BinarySearchTree* tree, int value);

/* If there is no element to remove, the function will return false.
 * If the node to be removed has both children,
 * the smallest element from the right subtree is removed. */
bool removeFromBinarySearchTree(BinarySearchTree* tree, int value);

/* The function returns an array of integers in the order that matches the traversal.
 * The choice of tree traversal depends on the choice of kindOfTraverse. */
int* traverseBinarySearchTree(BinarySearchTree* tree, Traverse kindOfTraverse);

bool isBinarySearchTreeEmpty(BinarySearchTree* tree);

int getSizeOfBinaryTree(BinarySearchTree* tree);

/* The function displays the tree in the console in the form:
 * (node (left subtree) (right subtree)).
 * If the tree is empty, the function will display "null". */
void printBinarySearchTree(BinarySearchTree* tree);

void deleteBinarySearchTree(BinarySearchTree* tree);

#endif //BINARYSEARCHTREE_H
