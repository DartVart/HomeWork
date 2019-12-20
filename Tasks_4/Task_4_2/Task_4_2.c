#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneBook.h"
#include "stringReading.h"

void displayInvitationToEnterAction(char* nameOfFile)
{
    printf("------------------NEW ACTION------------------\n"
           "Enter some of the following integers:\n"
           "\'0\' to exit;\n"
           "\'1\' to add user;\n"
           "\'2\' to find phone by name;\n"
           "\'3\' to find name by phone;\n"
           "\'4\' to write data to \"%s\":\n", nameOfFile);
}

bool scanNumber(int* number)
{
    return scanf("%d", number) == 1;
}

void getAction(int* action, char* nameOfFile)
{
    displayInvitationToEnterAction(nameOfFile);
    // validation of input
    bool isCorrectInput = false;
    do
    {
        isCorrectInput = scanNumber(action) && *action >= 0 && *action <= 4;
        if (!isCorrectInput)
        {
            printf("Please enter a valid value.\n");
        }
        fflush(stdin);
    } while (!isCorrectInput);
}

bool haveSpaces(char* string)
{
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        if (string[i] == ' ')
        {
            return true;
        }
    }
    return false;
}

void scanPhoneNumber(char* phoneNumber)
{
    scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);
    while (haveSpaces(phoneNumber))
    {
        printf("Please enter the phone number without spaces:\n");
        scanStringWithSpaces(stdin, phoneNumber, maxSizeOfPhoneNumber);
    }
}

//'name' and 'phoneNumber' are variables for reading name and phone number data
void addUser(PhoneBook* phoneBook, char* name, char* phoneNumber)
{
    printf("Enter user name:\n");
    scanStringWithSpaces(stdin, name, maxSizeOfName);

    printf("Enter user phone number (without spaces):\n");
    scanPhoneNumber(phoneNumber);

    addUserToPhoneBook(phoneBook, name, phoneNumber);
}

// 'name' and 'phoneNumber' are variables for reading name and phone number data
// The function reads the name from the console
void displayPhoneNumberByName(PhoneBook* phoneBook, char* name, char* phoneNumber)
{
    printf("Enter user name:\n");
    scanStringWithSpaces(stdin, name, maxSizeOfName);
    bool isFoundPhone = getPhoneByName(phoneBook, name, phoneNumber);

    if (isFoundPhone)
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
    printf("Enter user phone number:\n");
    scanPhoneNumber(phoneNumber);

    bool isFoundName = getNameByPhone(phoneBook, name, phoneNumber);

    if (isFoundName)
    {
        printf("Phone number %s is used by %s.\n", phoneNumber, name);
    }
    else
    {
        printf("There is no user with a phone number %s yet!\n", phoneNumber);
    }
}

bool processAction(int action, PhoneBook* phoneBook, FILE* fileOutput)
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
        case 1:
        {
            addUser(phoneBook, name, phoneNumber);
            break;
        }
        case 2:
        {
            displayPhoneNumberByName(phoneBook, name, phoneNumber);
            break;
        }
        case 3:
        {
            displayNameByPhoneNumber(phoneBook, name, phoneNumber);
            break;
        }
        case 4:
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
    int action = 0;
    getAction(&action, nameOfFile);
    while (action != 0)
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

    if (fileOutput == NULL)
    {
        printf("File open error.");
        return -1;
    }

    PhoneBook* phoneBook = initializePhoneBook(nameOfFile);

    if (phoneBook == NULL)
    {
        printf("Phone book initialization error.");
        return -1;
    }

    processUserActions(phoneBook, fileOutput, nameOfFile);

    fclose(fileOutput);
    deletePhoneBook(phoneBook);
    return 0;
}