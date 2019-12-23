#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phoneBook.h"
#include "stringReading.h"

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
bool setDataToPhoneBookFromFile(PhoneBook* phoneBook, char* nameOfFile)
{
    FILE* fileInput = fopen(nameOfFile, "a+");

    if (phoneBook == NULL || fileInput == NULL)
    {
        return false;
    }

    char* phoneNumber = NULL;
    char* name = NULL;

    while (!feof(fileInput))
    {
        phoneNumber = getStringFromStream(fileInput, readingWithoutSpaces);
        name = getStringFromStream(fileInput, readingWithSpaces);

        addUserToPhoneBook(phoneBook, name, phoneNumber);
        free(phoneNumber);
        free(name);
    }

    phoneBook->numberOfUsersInFile = phoneBook->numberOfUsers;

    fclose(fileInput);
    return true;
}

PhoneBook* initializePhoneBook(char* nameOfFile)
{
    PhoneBook* phoneBook = createEmptyPhoneBook();

    bool isCorrectInitialization = setDataToPhoneBookFromFile(phoneBook, nameOfFile);

    if (!isCorrectInitialization)
    {
        return NULL;
    }

    return phoneBook;
}

// If (sourceString == NULL), the function will return NULL
char* getClonedString(char* sourceString)
{
    if (sourceString == NULL)
    {
        return NULL;
    }
    int lengthOfString = strlen(sourceString);
    char* clonedString = (char*) malloc((lengthOfString + 1) * sizeof(char));
    strcpy(clonedString, sourceString);
    return clonedString;
}

// If (PhoneBook == NULL), the function will return false
bool setDataToPhoneUser(PhoneBook* phoneBook, char* name, char* phoneNumber, int currentNumberOfUsers)
{
    if (phoneBook == NULL || name == NULL || phoneNumber == NULL)
    {
        return false;
    }

    phoneBook->array[currentNumberOfUsers].name = getClonedString(name);
    phoneBook->array[currentNumberOfUsers].phoneNumber = getClonedString(phoneNumber);
    return true;
}

bool addUserToPhoneBook(PhoneBook* phoneBook, char* name, char* phoneNumber)
{
    if (phoneBook == NULL || name == NULL || phoneNumber == NULL)
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

bool hasName(PhoneBook* phoneBook, char* name)
{
    if (phoneBook == NULL || name == NULL)
    {
        return false;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].name, name))
        {
            return true;
        }
    }

    return false;
}

bool hasPhoneNumber(PhoneBook* phoneBook, char* phoneNumber)
{
    if (phoneBook == NULL || phoneNumber == NULL)
    {
        return false;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].phoneNumber, phoneNumber))
        {
            return true;
        }
    }

    return false;
}

char* getPhoneByName(PhoneBook* phoneBook, char* name)
{
    if (phoneBook == NULL || name == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].name, name))
        {
            char* desiredPhoneNumber = getClonedString(phoneBook->array[i].phoneNumber);
            return desiredPhoneNumber;
        }
    }

    return NULL;
}

char* getNameByPhone(PhoneBook* phoneBook, char* phoneNumber)
{
    if (phoneBook == NULL || phoneNumber == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        if (isStringEqual(phoneBook->array[i].phoneNumber, phoneNumber))
        {
            char* desiredName = getClonedString(phoneBook->array[i].name);
            return desiredName;
        }
    }

    return NULL;
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