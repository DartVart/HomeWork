#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phoneBook.h"
#include "stringReading.h"

const int maxSizeOfName = 40;
const int maxSizeOfPhoneNumber = 20;
const int initialCapacity = 10;

typedef struct PhoneUser PhoneUser;
struct PhoneUser
{
    char* name;
    char* phoneNumber;
};

struct PhoneBook
{
    PhoneUser* array;
    int numberOfUsers;
    int numberOfUsersInFile;
    int arrayCapacity;
};

PhoneBook* createEmptyPhoneBook()
{
    PhoneBook* phoneBook = (PhoneBook*) malloc(sizeof(PhoneBook));
    phoneBook->arrayCapacity = initialCapacity;
    phoneBook->numberOfUsers = 0;
    phoneBook->numberOfUsersInFile = 0;
    phoneBook->array = (PhoneUser*) malloc(phoneBook->arrayCapacity * sizeof(PhoneUser));
    return phoneBook;
}

//If (PhoneBook == NULL) or there was an error reading the file, the function will return false
bool setDataToPhoneBookFromFile(PhoneBook* phoneBook, char nameOfFile[])
{
    FILE* fileInput = fopen(nameOfFile, "a+");

    if (phoneBook == NULL || fileInput == NULL)
    {
        return false;
    }

    char* phoneNumber = (char*) calloc(maxSizeOfPhoneNumber, sizeof(char));
    char* name = (char*) calloc(maxSizeOfName, sizeof(char));

    // maxLengthOfLineInFile = maxSizeOfPhoneNumber - 1 (excluding '\0') + maxSizeOfName - 1 (excluding '\0') +
    // + 1 (space between number and name) + 1 ('\0' in the string itself)
    int maxLengthOfLineInFile = maxSizeOfPhoneNumber + maxSizeOfName;
    char* lineInFile = (char*) calloc(maxLengthOfLineInFile, sizeof(char));

    while (!feof(fileInput))
    {
        scanStringWithSpaces(fileInput, lineInFile, maxLengthOfLineInFile);
        sscanf(lineInFile, "%s %[^\n]", phoneNumber, name);

        addUserToPhoneBook(phoneBook, name, phoneNumber);
    }

    phoneBook->numberOfUsersInFile = phoneBook->numberOfUsers;

    fclose(fileInput);
    free(lineInFile);
    free(name);
    free(phoneNumber);
    return true;
}

PhoneBook* initializePhoneBook(char nameOfFile[])
{
    PhoneBook* phoneBook = createEmptyPhoneBook();

    bool isCorrectInitialization = setDataToPhoneBookFromFile(phoneBook, nameOfFile);

    if (!isCorrectInitialization)
    {
        return  NULL;
    }

    return phoneBook;
}

//If (PhoneBook == NULL), the function will return false
bool setDataToPhoneUser(PhoneBook* phoneBook, char name[], char phoneNumber[], int currentNumberOfUsers)
{
    if (phoneBook == NULL)
    {
        return false;
    }

    char* newPhoneNumber = (char*) calloc(maxSizeOfPhoneNumber, sizeof(char));
    char* newName = (char*) calloc(maxSizeOfName, sizeof(char));
    strcpy(newName, name);
    strcpy(newPhoneNumber, phoneNumber);

    phoneBook->array[currentNumberOfUsers].name = newName;
    phoneBook->array[currentNumberOfUsers].phoneNumber = newPhoneNumber;
    return true;
}

bool addUserToPhoneBook(PhoneBook* phoneBook, char name[], char phoneNumber[])
{
    if (phoneBook == NULL)
    {
        return false;
    }

    if (phoneBook->numberOfUsers == phoneBook->arrayCapacity)
    {
        phoneBook->arrayCapacity *= 2;
        phoneBook->array = (PhoneUser*) realloc(phoneBook->array, phoneBook->arrayCapacity * sizeof(PhoneUser));
    }

    int currentNumberOfUsers = phoneBook->numberOfUsers;
    setDataToPhoneUser(phoneBook, name, phoneNumber, currentNumberOfUsers);

    phoneBook->numberOfUsers++;
    return true;
}

bool isStringEqual(char* firstString, char* secondString)
{
    return strcmp(firstString, secondString) == 0;
}

bool getPhoneByName(PhoneBook* phoneBook, char name[], char desiredPhoneNumber[])
{
    if (phoneBook == NULL)
    {
        return false;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].name, name))
        {
            strcpy(desiredPhoneNumber, phoneBook->array[i].phoneNumber);
            return true;
        }
    }

    return false;
}

bool getNameByPhone(PhoneBook* phoneBook, char desiredName[], char phoneNumber[])
{
    if (phoneBook == NULL)
    {
        return false;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].phoneNumber, phoneNumber))
        {
            strcpy(desiredName, phoneBook->array[i].name);
            return true;
        }
    }

    return false;
}

bool writeDataToFile(PhoneBook* phoneBook, FILE* fileOutput)
{
    if (phoneBook == NULL || fileOutput == NULL)
    {
        return false;
    }

    for (int i = phoneBook->numberOfUsersInFile; i < phoneBook->numberOfUsers; i++)
    {
        fprintf(fileOutput, "%s %s\n", phoneBook->array[i].phoneNumber, phoneBook->array[i].name);
    }

    phoneBook->numberOfUsersInFile = phoneBook->numberOfUsers;
    return true;
}

bool deletePhoneBook(PhoneBook* phoneBook)
{
    if (phoneBook == NULL)
    {
        return false;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        free(phoneBook->array[i].name);
        free(phoneBook->array[i].phoneNumber);
    }
    free(phoneBook->array);
    free(phoneBook);
    return true;
}