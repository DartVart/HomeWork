#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phoneBook.h"

const int initialCapacity = 10;

typedef struct PhoneUser PhoneUser;
struct PhoneUser
{
    char name[maxSizeOfName];
    char phoneNumber[maxSizeOfPhoneNumber];
};

struct PhoneBook
{
    PhoneUser* array;
    int numberOfUsers;
    int numberOfUsersInFile;
    int arrayCapacity;
};

PhoneBook* initializePhoneBook(char nameOfFile[])
{
    char name[maxSizeOfName] = "";
    char phoneNumber[maxSizeOfPhoneNumber] = "";

    PhoneBook* phoneBook = (PhoneBook*) malloc(sizeof(phoneBook));

    phoneBook->arrayCapacity = initialCapacity;
    phoneBook->numberOfUsers = 0;
    phoneBook->numberOfUsersInFile = 0;
    phoneBook->array = (PhoneUser*) malloc(phoneBook->arrayCapacity * sizeof(PhoneUser));

    FILE* fileInput = fopen(nameOfFile, "a+");

    while (!feof(fileInput))
    {
        fscanf(fileInput, "%s %[^\n]", phoneNumber, name);

        addUserToPhoneBook(phoneBook, name, phoneNumber);
    }

    fclose(fileInput);

    phoneBook->numberOfUsersInFile = phoneBook->numberOfUsers;

    return phoneBook;
}

void addUserToPhoneBook(PhoneBook* phoneBook, char name[], char phoneNumber[])
{
    if (phoneBook->numberOfUsers == phoneBook->arrayCapacity)
    {
        phoneBook->arrayCapacity *= 2;
        phoneBook->array = (PhoneUser*) realloc(phoneBook->array, phoneBook->arrayCapacity * sizeof(PhoneUser));
    }

    int currentNumberOfUsers = phoneBook->numberOfUsers;
    strcpy(phoneBook->array[currentNumberOfUsers].name, name);
    strcpy(phoneBook->array[currentNumberOfUsers].phoneNumber, phoneNumber);
    phoneBook->numberOfUsers++;
}

bool getPhoneByName(PhoneBook* phoneBook, char name[], char desiredPhoneNumber[])
{
    bool isStringsEqual = false;
    int strcmpReturn = 0;
    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        strcmpReturn = strcmp(phoneBook->array[i].name, name);
        isStringsEqual = (strcmpReturn == 0);
        if (isStringsEqual)
        {
            strcpy(desiredPhoneNumber, phoneBook->array[i].phoneNumber);
            return true;
        }
    }

    return false;
}

bool getNameByPhone(PhoneBook* phoneBook, char desiredName[], char phoneNumber[])
{
    bool isStringsEqual = false;
    int strcmpReturn = 0;
    for (int i = 0; i < phoneBook->numberOfUsers; i++)
    {
        strcmpReturn = strcmp(phoneBook->array[i].phoneNumber, phoneNumber);
        isStringsEqual = (strcmpReturn == 0);
        if (isStringsEqual)
        {
            strcpy(desiredName, phoneBook->array[i].name);
            return true;
        }
    }

    return false;
}

void writeDataToFile(PhoneBook* phoneBook, FILE* fileOutput)
{
    for (int i = phoneBook->numberOfUsersInFile; i < phoneBook->numberOfUsers; i++)
    {
        fprintf(fileOutput, "%s %s\n", phoneBook->array[i].phoneNumber, phoneBook->array[i].name);
    }

    phoneBook->numberOfUsersInFile = phoneBook->numberOfUsers;
}

void deletedPhoneBook(PhoneBook* phoneBook)
{
    free(phoneBook->array);
    free(phoneBook);
}