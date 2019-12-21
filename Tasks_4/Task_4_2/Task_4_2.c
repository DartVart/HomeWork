#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneBook.h"
#include "stringReading.h"

void cleanStdin()
{
    int character;
    do
    {
        character = getchar();
    }
    while (character != EOF && character != '\n');
}

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

int getAction(char* nameOfFile)
{
    int action = 0;
    displayInvitationToEnterAction(nameOfFile);
    // validation of input
    bool isCorrectInput = false;
    do
    {
        isCorrectInput = scanNumber(&action) && action >= 0 && action <= 4;
        if (!isCorrectInput)
        {
            printf("Please enter a valid value.\n");
        }
        cleanStdin();
    } while (!isCorrectInput);
    return action;
}

bool hasSpaces(char* string)
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

char* scanPhoneNumberFromConsole()
{
    char* phoneNumber = getStringFromStream(stdin, readingWithSpaces);
    while (hasSpaces(phoneNumber))
    {
        printf("Please enter the phone number without spaces:\n");
        free(phoneNumber);
        phoneNumber = getStringFromStream(stdin, readingWithSpaces);
    }
    return phoneNumber;
}

void addUser(PhoneBook* phoneBook)
{
    printf("Enter user name:\n");
    char* name = getStringFromStream(stdin, readingWithSpaces);
    while (hasName(phoneBook, name))
    {
        printf("Sorry, but this name already exists in the book. Try another:\n");
        free(name);
        name = getStringFromStream(stdin, readingWithSpaces);
    }

    printf("Enter user phone number (without spaces):\n");
    char* phoneNumber = scanPhoneNumberFromConsole();
    while (hasPhoneNumber(phoneBook, phoneNumber))
    {
        printf("Sorry, but this phone number already exists in the book. Try another:\n");
        free(phoneNumber);
        phoneNumber = scanPhoneNumberFromConsole();
    }

    addUserToPhoneBook(phoneBook, name, phoneNumber);
    free(name);
    free(phoneNumber);
}

// The function reads the name from the console
void displayPhoneNumberByName(PhoneBook* phoneBook)
{
    printf("Enter user name:\n");
    char* name = getStringFromStream(stdin, readingWithSpaces);
    char* phoneNumber = getPhoneByName(phoneBook, name);

    if (phoneNumber != NULL)
    {
        printf("%s uses phone number %s.\n", name, phoneNumber);
    }
    else
    {
        printf("%s doesn't have a phone number yet!\n", name);
    }

    free(name);
    free(phoneNumber);
}

// The function reads the phone number from the console
void displayNameByPhoneNumber(PhoneBook* phoneBook)
{
    printf("Enter user phone number:\n");
    char* phoneNumber = scanPhoneNumberFromConsole();
    char* name = getNameByPhone(phoneBook, phoneNumber);

    if (name != NULL)
    {
        printf("Phone number %s is used by %s.\n", phoneNumber, name);
    }
    else
    {
        printf("There is no user with a phone number %s yet!\n", phoneNumber);
    }
    free(name);
    free(phoneNumber);
}

bool processAction(int action, PhoneBook* phoneBook, FILE* fileOutput)
{
    if (phoneBook == NULL || fileOutput == NULL)
    {
        return false;
    }

    switch (action)
    {
        case 1:
        {
            addUser(phoneBook);
            break;
        }
        case 2:
        {
            displayPhoneNumberByName(phoneBook);
            break;
        }
        case 3:
        {
            displayNameByPhoneNumber(phoneBook);
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
    return true;
}

void processUserActions(PhoneBook* phoneBook, FILE* fileOutput, char* nameOfFile)
{
    bool isCorrectProcessing = true;
    int action = getAction(nameOfFile);
    while (action != 0)
    {
        isCorrectProcessing = processAction(action, phoneBook, fileOutput);
        if (!isCorrectProcessing)
        {
            printf("Action processing error.");
            return;
        }
        action = getAction(nameOfFile);
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