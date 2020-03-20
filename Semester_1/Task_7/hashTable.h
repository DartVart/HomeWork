#pragma once

#include <stdbool.h>
#include "myString.h"

typedef struct HashTable HashTable;
struct HashTable;

HashTable* createHashTable(int initialCapacity, double maxLoadFactor);

double getLoadFactor(HashTable* hashTable);

bool addToHashTable(HashTable* hashTable, MyString* key, int value);

int getValueByKey(MyString* key, HashTable* hashtable);

bool setValueByKey(HashTable* hashTable, MyString* key, int value);

bool isInHashTable(MyString* key, HashTable* hashTable);

void deleteHashTable(HashTable* hashTable);

bool deleteFromHashTable(MyString* key, HashTable* hashTable);

bool printHashTable(HashTable* hashTable, FILE* outputStream);

bool printHashTableInformation(HashTable* hashTable, FILE* outputStream);