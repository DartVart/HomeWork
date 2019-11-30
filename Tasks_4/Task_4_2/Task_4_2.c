#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneBook.h"
#include "stringReading.h"

const int maxSizeOfString = 5;

enum Action
{
    EXIT,
    ADD_USER,
    FIND_PHONE_NUMBER,
    FIND_NAME,
    WRITE_TO_FILE
};

void displayInvitationToEnterAction(char* nameOfFile)
{
    printf("------------------NEW ACTION------------------\n"
           "Enter some of the following integers: \n"
           "\'0\' to exit;\n"
           "\'1\' to add user;\n"
           "\'2\' to find phone by name;\n"
           "\'3\' to find name by phone;\n"
           "\'4\' to write data to \"%s\": \n", nameOfFile);
}

int convertCharToDigit(char symbol)
{
    return symbol - '0';
}

void getAction(enum Action* action, char* nameOfFile)
{
    displayInvitationToEnterAction(nameOfFile);
    // validation of input
    char* inputString = (char*) calloc(maxSizeOfString, sizeof(char));
    bool isCorrectInput = false;
    while (!isCorrectInput)
    {
        fflush(stdin);
        scanf("%2s", inputString);

        isCorrectInput = strlen(inputString) == 1 && inputString[0] >= '0' && inputString[0] <= '4';
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
    printf("===================PHONE BOOK===================\n");

    char nameOfFile[] = "Phone_book.txt";

    PhoneBook* phoneBook = initializePhoneBook(nameOfFile);

    FILE* fileOutput = fopen(nameOfFile, "a+");

    // maxSizeOfPhoneNumber and maxSizeOfName declared in "phoneBook.h"
    char* phoneNumber = (char*) calloc(maxSizeOfPhoneNumber, sizeof(char));
    char* name = (char*) calloc(maxSizeOfName, sizeof(char));
    bool isFindObject = false;
    enum Action action = 0;
    getAction(&action, nameOfFile);
    while (action != EXIT)
    {
        switch (action)
        {
            case ADD_USER:
            {
                printf("Enter user name: ");
                scanStringWithSpaces(stdin, name, maxSizeOfName);

                printf("Enter user phone number (without spaces): ");
                scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);

                addUserToPhoneBook(phoneBook, name, phoneNumber);

                break;
            }

            case FIND_PHONE_NUMBER:
            {
                printf("Enter user name: ");
                scanStringWithSpaces(stdin, name, maxSizeOfName);

                isFindObject = getPhoneByName(phoneBook, name, phoneNumber);

                if (isFindObject)
                {
                    printf("%s uses phone number %s.\n", name, phoneNumber);
                }
                else
                {
                    printf("%s doesn't have a phone number yet!\n", name);
                }

                break;
            }

            case FIND_NAME:
            {
                printf("Enter user phone number (without spaces): ");
                scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);

                isFindObject = getNameByPhone(phoneBook, name, phoneNumber);

                if (isFindObject)
                {
                    printf("Phone number %s is used by %s.\n", phoneNumber, name);
                }
                else
                {
                    printf("There is no user with a phone number %s yet!\n", phoneNumber);
                }

                break;
            }

            case WRITE_TO_FILE:
            {
                writeDataToFile(phoneBook, fileOutput);
                break;
            }

            default:
            {
                break;
            }
        }

        getAction(&action, nameOfFile);
    }

    free(name);
    free(phoneNumber);
    fclose(fileOutput);
    deletePhoneBook(phoneBook);
    return 0;
}