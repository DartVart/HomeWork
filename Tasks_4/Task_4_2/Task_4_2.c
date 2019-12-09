#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneBook.h"
#include "stringReading.h"

const int maxSizeOfString = 5;

typedef enum Action
{
    EXIT = 0,
    ADD_USER = 1,
    DISPLAY_PHONE_NUMBER_BY_NAME = 2,
    DISPLAY_NAME_BY_PHONE_NUMBER = 3,
    WRITE_TO_FILE = 4
} Action;

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

void getAction(Action* action, char* nameOfFile)
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

//'name' and 'phoneNumber' are variables for reading name and phone number data
void addUser(PhoneBook* phoneBook, char* name, char* phoneNumber)
{
    printf("Enter user name: ");
    scanStringWithSpaces(stdin, name, maxSizeOfName);

    printf("Enter user phone number (without spaces): ");
    scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);

    addUserToPhoneBook(phoneBook, name, phoneNumber);
}

// 'name' and 'phoneNumber' are variables for reading name and phone number data
// The function reads the name from the console
void displayPhoneNumberByName(PhoneBook* phoneBook, char* name, char* phoneNumber)
{
    printf("Enter user name: ");
    scanStringWithSpaces(stdin, name, maxSizeOfName);
    bool isFindPhone = getPhoneByName(phoneBook, name, phoneNumber);

    if (isFindPhone)
    {
        printf("%s uses phone number %s.\n", name, phoneNumber);
    }
    else
    {
        printf("%s doesn't have a phone number yet!\n", name);
    }
}

// 'name' and 'phoneNumber' are variables for reading name and phone number data
// The function reads the phone number from the console
void displayNameByPhoneNumber(PhoneBook* phoneBook, char* name, char* phoneNumber)
{

    printf("Enter user phone number (without spaces): ");
    scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);

    bool isFindName = getNameByPhone(phoneBook, name, phoneNumber);

    if (isFindName)
    {
        printf("Phone number %s is used by %s.\n", phoneNumber, name);
    }
    else
    {
        printf("There is no user with a phone number %s yet!\n", phoneNumber);
    }
}

bool processAction(Action action, PhoneBook* phoneBook, FILE* fileOutput)
{
    // maxSizeOfPhoneNumber and maxSizeOfName declared in "phoneBook.h"
    char* phoneNumber = (char*) calloc(maxSizeOfPhoneNumber, sizeof(char));
    char* name = (char*) calloc(maxSizeOfName, sizeof(char));

    if (phoneBook == NULL || fileOutput == NULL)
    {
        return false;
    }

    switch (action)
    {
        case ADD_USER:
        {
            addUser(phoneBook, name, phoneNumber);
            break;
        }
        case DISPLAY_PHONE_NUMBER_BY_NAME:
        {
            displayPhoneNumberByName(phoneBook, name, phoneNumber);
            break;
        }
        case DISPLAY_NAME_BY_PHONE_NUMBER:
        {
            displayNameByPhoneNumber(phoneBook, name, phoneNumber);
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
    free(name);
    free(phoneNumber);
    return true;
}

void processUserActions(PhoneBook* phoneBook, FILE* fileOutput, char* nameOfFile)
{
    bool isCorrectProcessing = true;
    Action action = 0;
    getAction(&action, nameOfFile);
    while (action != EXIT)
    {
        isCorrectProcessing = processAction(action, phoneBook, fileOutput);
        if (!isCorrectProcessing)
        {
            printf("Action processing error.");
            return;
        }
        getAction(&action, nameOfFile);
    }
}

int main()
{
    printf("===================PHONE BOOK===================\n");

    char nameOfFile[] = "Phone_book.txt";

    FILE* fileOutput = fopen(nameOfFile, "a+");

    PhoneBook* phoneBook = initializePhoneBook(nameOfFile);

    processUserActions(phoneBook, fileOutput, nameOfFile);

    fclose(fileOutput);
    deletePhoneBook(phoneBook);
    return 0;
}