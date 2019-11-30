/**
 * The module supports file data processing.
 * Data about one user should be written in a file in the form:
 * "<phone (a string without spaces, tabs, newline)> <username (spaces are allowed)><newline>".
 */
#pragma once

#include <stdbool.h>

extern const int maxSizeOfName;
extern const int maxSizeOfPhoneNumber;

typedef struct PhoneBook PhoneBook;
struct PhoneBook;

/* nameOfFile contains the name of file with data about users.
 * If the file is missing, then it's created.
 * In case of an initialization error, the function will return NULL. */
PhoneBook* initializePhoneBook(char nameOfFile[]);

/* If (PhoneBook == NULL), the function will return false. */
bool addUserToPhoneBook(PhoneBook* phoneBook, char name[], char phoneNumber[]);

/* The phone number will be placed in the desiredPhoneNumber.
 * If (PhoneBook == NULL) or name was not found, the function will return false. */
bool getPhoneByName(PhoneBook* phoneBook, char name[], char desiredPhoneNumber[]);

/* The name will be placed in the desiredName.
 * If (PhoneBook == NULL) or phone number was not found, the function will return false. */
bool getNameByPhone(PhoneBook* phoneBook, char desiredName[], char phoneNumber[]);

/* The file should be opened with the following access mode flags: "a", "a+".
 * If (PhoneBook == NULL) or there was an error reading the file, the function will return false. */
bool writeDataToFile(PhoneBook* phoneBook, FILE* fileOutput);

/* If (PhoneBook == NULL), the function will return false. */
bool deletePhoneBook(PhoneBook* phoneBook);