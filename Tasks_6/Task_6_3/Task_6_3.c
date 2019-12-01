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

int main()
{
    Set* set = createSet();
    int* setAsArray = (int*) malloc(0);
    int sizeOfSet = 0;

    int value = 0;
    bool isValueInSet = false;
    Action action = 0;
    getAction(&action);
    while (action != EXIT)
    {
        switch (action)
        {
            case ADD_ELEMENT:
            {
                printf("Enter value:" );
                scanf("%d", &value);
                insertToSet(set, value);
                break;
            }

            case REMOVE_ELEMENT:
            {
                printf("Enter value:" );
                scanf("%d", &value);
                removeFromSet(set, value);
                break;
            }

            case CHECK_AFFILIATION_OF_ELEMENT:
            {
                printf("Enter value:" );
                scanf("%d", &value);
                isValueInSet = isInSet(set, value);
                if (isValueInSet)
                {
                    printf("Number %d is in the set!\n", value);
                }
                else
                {
                    printf("Number %d isn't in set!\n", value);
                }
                break;
            }

            case PRINT_IN_ASCENDING_ORDER:
            {
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
                break;
            }

            case PRINT_IN_DESCENDING_ORDER:
            {
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
                break;
            }

            case PRINT_SET:
            {
                printf("The set: \n");
                printSet(set);
                printf("\n");
                break;
            }

            default:
            {
                break;
            }
        }

        getAction(&action);
    }

    deleteSet(set);
    return 0;
}