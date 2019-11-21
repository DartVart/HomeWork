/**
 * The module supports file data processing.
 * Data about one user should be written in a file in the form:
 * "<phone (a string without spaces, tabs, newline)> <username (spaces are allowed)><newline>".
 */

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <stdbool.h>

const int maxSizeOfName = 40;
const int maxSizeOfPhoneNumber = 20;

typedef struct PhoneBook PhoneBook;
struct PhoneBook;

/* nameOfFile contains the name of file with data about users.
 * If the file is missing, then it's created. */
PhoneBook* initializePhoneBook(char nameOfFile[]);

void addUserToPhoneBook(PhoneBook* phoneBook, char name[], char phoneNumber[]);

/* The phone number will be placed in the desiredPhoneNumber. */
bool getPhoneByName(PhoneBook* phoneBook, char name[], char desiredPhoneNumber[]);

/* The name will be placed in the desiredName. */
bool getNameByPhone(PhoneBook* phoneBook, char desiredName[], char phoneNumber[]);

/* The file should be opened with the following access mode flags: "a", "a+". */
void writeDataToFile(PhoneBook* phoneBook, FILE* fileOutput);

void deletePhoneBook(PhoneBook* phoneBook);

#endif //PHONEBOOK_H
