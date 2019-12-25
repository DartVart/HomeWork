#include <stdio.h>
#include "hashTable.h"
#include "myString.h"

const int initialCapacity = 30;
const double maxLoadFactor = 0.7;

int main()
{
    char nameOfFile[] = "input_text.txt";

    FILE* fileInput = fopen(nameOfFile, "r");

    if (fileInput == NULL)
    {
        printf("File open error.");
        return -1;
    }

    HashTable* hashTable = createHashTable(initialCapacity, maxLoadFactor);

    MyString* word = getStringFromStream(fileInput, readingWithoutSpaces);

    int numberOfEntries = 0;
    while (word != NULL)
    {
        if (!isInHashTable(word, hashTable))
        {
            addToHashTable(hashTable, word, 1);
        }
        else
        {
            numberOfEntries = getValueByKey(word, hashTable);
            numberOfEntries++;
            setValueByKey(hashTable, word, numberOfEntries);
        }
        deleteString(word);
        word = getStringFromStream(fileInput, readingWithoutSpaces);
    }

    printf("Words occurring in the text in the following format:\n");
    printf("\"<text>; <how many times the string occurs in the text>\":\n");
    printHashTable(hashTable, stdout);
    printf("\n");
    printHashTableInformation(hashTable, stdout);

    deleteHashTable(hashTable);
    fclose(fileInput);
    return 0;
}
