#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

void cleanStdin()
{
    int character;
    do
    {
        character = getchar();
    } while (character != EOF && character != '\n');
}

void printArrayInDirectOrder(int* array, int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d ", array[i]);
    }
}

void printArrayInReverseOrder(int* array, int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; i--)
    {
        printf("%d ", array[i]);
    }
}

void displayInvitationToEnterAction()
{
    printf("------------------------------------NEW ACTION------------------------------------\n"
           "Enter some of the following integers: \n"
           "\'0\' to exit;\n"
           "\'1\' to add an element to the set;\n"
           "\'2\' to remove an element from the set;\n"
           "\'3\' to check if an element belongs to the set;\n"
           "\'4\' to print the set in ascending order;\n"
           "\'5\' to print the set in descending order;\n"
           "\'6\' to print the set (as a tree) in form: (node (left subtree) (right subtree)):\n");
}

void scanNumber(int* number)
{
    bool isCorrectInput = false;
    do
    {
        isCorrectInput = scanf("%d", number) == 1;
        if (!isCorrectInput)
        {
            printf("Please enter a number.\n");
        }
        cleanStdin();
    } while (!isCorrectInput);
}

void getAction(int* action)
{
    displayInvitationToEnterAction();
    // validation of input
    bool isCorrectInput = false;
    do
    {
        scanNumber(action);
        isCorrectInput = *action >= 0 && *action <= 6;
        if (!isCorrectInput)
        {
            printf("Please enter a valid value.\n");
        }
    } while (!isCorrectInput);
}

void addElement(Set* set)
{
    int value = 0;
    printf("Enter a value:\n");
    scanNumber(&value);
    insertToSet(set, value);
}

void removeElement(Set* set)
{
    int value = 0;
    printf("Enter a value:\n");
    scanNumber(&value);
    if (isInSet(set, value))
    {
        removeFromSet(set, value);
    }
    else
    {
        printf("Error of removing. Number %d isn't in the set!\n", value);
    }
}

void checkAffiliationOfElement(Set* set)
{
    int value = 0;
    printf("Enter value:\n");
    scanNumber(&value);
    bool isValueInSet = isInSet(set, value);
    if (isValueInSet)
    {
        printf("Number %d is in the set!\n", value);
    }
    else
    {
        printf("Number %d isn't in the set!\n", value);
    }
}

void printSetInAscendingOrder(Set* set)
{
    int sizeOfSet = 0;
    if (isSetEmpty(set))
    {
        printf("The set is empty!\n");
    }
    else
    {
        sizeOfSet = getSizeOfSet(set);
        int* setAsArray = getSetInAscendingOrder(set);
        printf("The set: \n");
        printArrayInDirectOrder(setAsArray, sizeOfSet);
        printf("\n");
        free(setAsArray);
    }
}

void printSetInDescendingOrder(Set* set)
{
    int sizeOfSet = 0;
    if (isSetEmpty(set))
    {
        printf("The set is empty!\n");
    }
    else
    {
        sizeOfSet = getSizeOfSet(set);
        int* setAsArray = getSetInAscendingOrder(set);
        printf("The set:\n");
        printArrayInReverseOrder(setAsArray, sizeOfSet);
        printf("\n");
        free(setAsArray);
    }
}

void printSet(Set* set)
{
    printf("The set:\n");
    printSetAsTree(set);
    printf("\n");
}

/* If (set == NULL), the function will return false. */
bool processAction(int action, Set* set)
{
    if (set == NULL)
    {
        return false;
    }

    switch (action)
    {
        case 1:
        {
            addElement(set);
            break;
        }
        case 2:
        {
            removeElement(set);
            break;
        }
        case 3:
        {
            checkAffiliationOfElement(set);
            break;
        }
        case 4:
        {
            printSetInAscendingOrder(set);
            break;
        }
        case 5:
        {
            printSetInDescendingOrder(set);
            break;
        }
        case 6:
        {
            printSet(set);
            break;
        }
        default:
        {
            break;
        }
    }
    return true;
}

void processUserActions(Set* set)
{
    bool isCorrectProcessing = false;

    int action = 0;
    getAction(&action);
    while (action != 0)
    {
        isCorrectProcessing = processAction(action, set);
        if (!isCorrectProcessing)
        {
            printf("Action processing error: the set are not initialized.\n");
            return;
        }
        getAction(&action);
    }
}

int main()
{
    Set* set = createSet();

    processUserActions(set);

    deleteSet(set);
    return 0;
}