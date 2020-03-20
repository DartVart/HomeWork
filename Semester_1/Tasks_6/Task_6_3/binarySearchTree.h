/**
 * This module implements an unbalanced binary search tree.
 */

#pragma once

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;
struct BinarySearchTree;

typedef enum Traverse Traverse;
enum Traverse
{
    prefixTraverse = 0,
    infixTraverse = 1,
    postfixTraverse = 2
};

BinarySearchTree* createBinarySearchTree();

/* If (tree == NULL), the function will return false. */
bool insertToBinarySearchTree(BinarySearchTree* tree, int value);

/* If (tree == NULL) or there is no suitable element in the tree, the function will return false. */
bool isInBinarySearchTree(BinarySearchTree* tree, int value);

/* If the node to be removed has right children,
 * the smallest element from the right subtree is removed.
 * If (tree == NULL), the function will return false. */
bool removeFromBinarySearchTree(BinarySearchTree* tree, int value);

/* The function returns an array of integers in the order that matches the traversal.
 * The choice of tree traversal depends on the choice of kindOfTraverse.
 * If (tree == NULL), the function will return NULL. */
int* traverseBinarySearchTree(BinarySearchTree* tree, Traverse kindOfTraverse);

bool isBinarySearchTreeEmpty(BinarySearchTree* tree);

/* If (tree == NULL), the function will return -1. */
int getSizeOfBinaryTree(BinarySearchTree* tree);

/* The function displays the tree in the console in the form:
 * (node (left subtree) (right subtree)).
 * If the tree is empty, the function will display "null", but
 * if (tree == NULL), the function will return false. */
bool printBinarySearchTree(BinarySearchTree* tree);

void deleteBinarySearchTree(BinarySearchTree* tree);