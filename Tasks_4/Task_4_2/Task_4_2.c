#include <stdio.h>
#include <stdbool.h>
#include "phoneBook.h"

void scanStringWithSpaces(FILE* inputStream, char* stringBuffer)
{
    fflush(inputStream);
    scanf("%[^\n]", stringBuffer);
}

enum Action
{
    EXIT,
    ADD_USER,
    FIND_PHONE_NUMBER,
    FIND_NAME,
    WRITE_TO_FILE
};

void getAction(enum Action* action, char* nameOfFile)
{
    printf("------------------NEW ACTION------------------\n"
           "Enter some of the following integers: \n"
           "\'0\' to exit;\n"
           "\'1\' to add user;\n"
           "\'2\' to find phone by name;\n"
           "\'3\' to find name by phone;\n"
           "\'4\' to write data to \"%s\": \n", nameOfFile);
    scanf("%d", action);
}

int main()
{
    printf("===================PHONE BOOK===================\n");

    char nameOfFile[] = "Phone_book.txt";

    PhoneBook* phoneBook = initializePhoneBook(nameOfFile);

    FILE* fileOutput = fopen(nameOfFile, "a+");

    // maxSizeOfPhoneNumber and maxSizeOfName declared in "phoneBook.h"
    char phoneNumber[maxSizeOfPhoneNumber] = "";
    char name[maxSizeOfName] = "";

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
                scanStringWithSpaces(stdin, name);

                printf("Enter user phone number: ");
                scanf("%s", phoneNumber);

                addUserToPhoneBook(phoneBook, name, phoneNumber);

                break;
            }

            case FIND_PHONE_NUMBER:
            {
                printf("Enter user name: ");
                scanStringWithSpaces(stdin, name);

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
                printf("Enter user phone number: ");
                scanf("%s", phoneNumber);

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

    fclose(fileOutput);
    deletePhoneBook(phoneBook);
    return 0;
}