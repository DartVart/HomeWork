/**
 * The module supports file data processing.
 * Data about one user should be written in a file in the form:
 * "<phone (a string without spaces, tabs, newline)> <username (spaces are allowed)><newline>".
 */

#pragma once

#include <stdbool.h>

typedef struct PhoneBook PhoneBook;
struct PhoneBook;

/* nameOfFile contains the name of file with data about users.
 * If the file is missing, then it's created.
 * In case of an initialization error, the function will return NULL. */
PhoneBook* initializePhoneBook(char* nameOfFile);

/* If (PhoneBook == NULL), the function will return false. */
bool addUserToPhoneBook(PhoneBook* phoneBook, char* name, char* phoneNumber);

bool hasName(PhoneBook* phoneBook, char* name);

bool hasPhoneNumber(PhoneBook* phoneBook, char* phoneNumber);

/* If (PhoneBook == NULL) or name was not found, the function will return NULL. */
char* getPhoneByName(PhoneBook* phoneBook, char* name);

/* If (PhoneBook == NULL) or phone number was not found, the function will return NULL. */
char* getNameByPhone(PhoneBook* phoneBook, char* phoneNumber);

/* The file should be opened with the following access mode flags: "a", "a+".
 * If (PhoneBook == NULL) or there was an error reading the file, the function will return false. */
bool writeDataToFile(PhoneBook* phoneBook, FILE* fileOutput);

/* If (PhoneBook == NULL), the function will return false. */
bool deletePhoneBook(PhoneBook* phoneBook);