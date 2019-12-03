#include <stdio.h>
#include <stdlib.h>
#include "myString.h"

#define maxSizeOfArray 4
#define maxSizeOfString 1000


typedef enum Action Action;
enum Action
{
    EXIT,
    SET_STRING_IN_ARRAY,
    CLONE_STRING,
    PRINT_STRING,
    PRINT_ALL_ARRAY,
    CHECKING_EQUALING,///????
    GET_SIZE_OF_STRING,
    GET_SUBSTRING
};

void scanStringFromConsole(char string[])
{
    fflush(stdin);
    fgets(string, maxSizeOfString, stdin);
}

void printArray(MyString array[], int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d elem: %s\n", i, stringToChar(&array[i]));
    }
}

void getAction(enum Action* action)
{
    printf("---------------------------------------------------------------\n"
           "Enter some of the following integers: \n"
           "\'0\' to exit;\n"
           "\'1\' to set data to array element;\n"////////////////////////////////////????????????????????????
           "\'2\' to clone string;\n"
           "\'3\' to print string;\n"
           "\'4\' to print all array; \n"
           "\'5\' to checking equaling; \n"////////////////????????????????????????????
           "\'6\' to get size of string: \n"
           "\'7\' to get substring: \n");
    scanf("%d", action);
}

MyString* createArrayOfString(int sizeOfArray)
{
    MyString* arrayOfString = (MyString*) malloc(sizeOfArray * sizeof(MyString));
    for (int i = 0; i < sizeOfArray; i++)
    {
        arrayOfString[i] = createString("");
    }

    return arrayOfString;
}

int main()
{
    MyString* arrayOfString = createArrayOfString(maxSizeOfArray);

    int array[maxSizeOfString] = {};

    char stringAsCharArray[maxSizeOfString] = "";
    int index = 0;
    int indexForCloning = 0;
    int firstSubstringIndex = 0;
    int secondSubstringIndex = 0;
    Action action = 0;
    getAction(&action);
    while (true)
    {
        switch (action)
        {
            case EXIT:
            {
                for (int i = 0; i < maxSizeOfArray; i++)
                {
                    deleteString(&arrayOfString[i]);
                }
                return 0;
            }

            case SET_STRING_IN_ARRAY:
            {
                printf("Enter string:" );
                scanStringFromConsole(stringAsCharArray);
                printf("Enter index:" );
                scanf("%d", &index);
                charToString(&arrayOfString[index], stringAsCharArray);
                break;
            }

            case CLONE_STRING:
            {
                //first to second
                printf("Enter first index:" );
                scanf("%d", &index);
                printf("Enter second index:" );
                scanf("%d", &indexForCloning);
                free(&arrayOfString[index]);
                cloneString(&arrayOfString[index], &arrayOfString[indexForCloning]);
                break;
            }
            case PRINT_STRING:
            {
                printf("Enter index:" );
                scanf("%d", &index);
                printf("This string:\n" );
                printString(&arrayOfString[index], stdin);
                break;
            }

            case PRINT_ALL_ARRAY:
            {
                printf("All array: \n" );
                printArray(arrayOfString, maxSizeOfArray);
                break;
            }

            case CHECKING_EQUALING:
            {
                printf("Enter first index:" );
                scanf("%d", &index);
                printf("Enter second index:" );
                scanf("%d", &indexForCloning);
                if (isStringEqual(&arrayOfString[index], &arrayOfString[indexForCloning]))
                {
                    printf("These strings are equal!");
                }
                else
                {
                    printf("These strings are different!");
                }
                break;
            }

            case GET_SIZE_OF_STRING:
            {
                printf("Enter index:" );
                scanf("%d", &index);
                printf("Size of \"");
                printString(&arrayOfString[index], stdin);
                printf("\": %d", getSizeOfString(&arrayOfString[index]));
                break;
            }

            case GET_SUBSTRING:
            {
                printf("Enter index:" );
                scanf("%d", &index);
                printf("Enter first index of string:" );
                scanf("%d", &firstSubstringIndex);
                printf("Enter second index of string:" );
                scanf("%d", &secondSubstringIndex);
                printString(getSubstring(&arrayOfString[index], firstSubstringIndex, secondSubstringIndex), stdin);
                break;
            }

            default:
            {
                break;
            }
        }

        getAction(&action);
    }
}