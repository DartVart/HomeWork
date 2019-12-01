#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

const int maxSizeOfString = 5;

typedef enum Action Action;
enum Action
{
    EXIT,
    ADD_ELEMENT,
    REMOVE_ELEMENT,
    CHECK_AFFILIATION_OF_ELEMENT,
    PRINT_IN_ASCENDING_ORDER,
    PRINT_IN_DESCENDING_ORDER,
    PRINT_SET
};

void printArrayInDirectOrder(int array[], int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d ", array[i]);
    }
}

void printArrayInReverseOrder(int array[], int sizeOfArray)
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
           "\'4\' to print the set in ascending order; \n"
           "\'5\' to print the set in descending order; \n"
           "\'6\' to print the set (as a tree) in form: (node (left subtree) (right subtree)): \n");
}

int convertCharToDigit(char symbol)
{
    return symbol - '0';
}

void getAction(enum Action* action)
{
    displayInvitationToEnterAction();
    // validation of input
    char* inputString = (char*) calloc(maxSizeOfString, sizeof(char));
    bool isCorrectInput = false;
    while (!isCorrectInput)
    {
        fflush(stdin);
        scanf("%2s", inputString);

        isCorrectInput = strlen(inputString) == 1 && inputString[0] >= '0' && inputString[0] <= '6';
        if (!isCorrectInput)
        {
            printf("Please enter a valid value.\n");
        }
    }

    *action = convertCharToDigit(inputString[0]);
    free(inputString);
}

void addElement(Set* set)
{
    int value = 0;
    printf("Enter value:" );
    scanf("%d", &value);
    insertToSet(set, value);
}

void removeElement(Set* set)
{
    int value = 0;
    printf("Enter value:" );
    scanf("%d", &value);
    removeFromSet(set, value);
}

void checkAffiliationOfElement(Set* set)
{
    int value = 0;
    printf("Enter value:" );
    scanf("%d", &value);
    bool isValueInSet = isInSet(set, value);
    if (isValueInSet)
    {
        printf("Number %d is in the set!\n", value);
    }
    else
    {
        printf("Number %d isn't in set!\n", value);
    }
}

void printSetInAscendingOrder(Set* set, int* setAsArray)
{
    int sizeOfSet = 0;
    if (isSetEmpty(set))
    {
        printf("The set is empty!\n");
    }
    else
    {
        sizeOfSet = getSizeOfSet(set);
        free(setAsArray);
        setAsArray = getSetInAscendingOrder(set);
        printf("The set: \n");
        printArrayInDirectOrder(setAsArray, sizeOfSet);
        printf("\n");
    }
}

void printSetInDescendingOrder(Set* set, int* setAsArray)
{
    int sizeOfSet = 0;
    if (isSetEmpty(set))
    {
        printf("The set is empty!\n");
    }
    else
    {
        sizeOfSet = getSizeOfSet(set);
        free(setAsArray);
        setAsArray = getSetInAscendingOrder(set);
        printf("The set: \n");
        printArrayInReverseOrder(setAsArray, sizeOfSet);
        printf("\n");
    }
}

void printSet(Set* set)
{
    printf("The set: \n");
    printSetAsTree(set);
    printf("\n");
}

void processUserActions(Set* set)
{
    int* setAsArray = (int*) malloc(0);
    Action action = 0;
    getAction(&action);
    while (action != EXIT)
    {
        switch (action)
        {
            case ADD_ELEMENT:
            {
                addElement(set);
                break;
            }

            case REMOVE_ELEMENT:
            {
                removeElement(set);
                break;
            }

            case CHECK_AFFILIATION_OF_ELEMENT:
            {
                checkAffiliationOfElement(set);
                break;
            }

            case PRINT_IN_ASCENDING_ORDER:
            {
                printSetInAscendingOrder(set, setAsArray);
                break;
            }

            case PRINT_IN_DESCENDING_ORDER:
            {
                printSetInDescendingOrder(set, setAsArray);
                break;
            }

            case PRINT_SET:
            {
                printSet(set);
                break;
            }

            default:
            {
                break;
            }
        }
        getAction(&action);
    }

    free(setAsArray);
}

int main()
{
    Set* set = createSet();

    processUserActions(set);

    deleteSet(set);
    return 0;
}