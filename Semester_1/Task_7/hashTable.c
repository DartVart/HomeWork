#include <stdlib.h>
#include "hashTable.h"

const int primeNumber = 91;

typedef struct Bucket
{
    MyString* key;
    int value;
    int numberOfAttemptsToInsert;
    bool isDeleted;
} Bucket;

struct HashTable
{
    Bucket** bucketArray;
    int capacity;
    int size;
    double maxLoadFactor;
};

double binaryPower(double base, int power)
{
    if (power == 0)
    {
        return 1;
    }

    double halfPower = binaryPower(base, power / 2);

    if (power % 2 == 1)
    {
        return halfPower * halfPower * base;
    }
    else
    {
        return halfPower * halfPower;
    }
}

double getPower(double base, int power)
{
    return (power >= 0) ? binaryPower(base, power) : 1 / binaryPower(base, -power);
}

HashTable* createHashTable(int initialCapacity, double maxLoadFactor)
{
    HashTable* hashTable = (HashTable*) malloc(sizeof(HashTable));
    hashTable->size = 0;
    hashTable->maxLoadFactor = maxLoadFactor;
    hashTable->capacity = initialCapacity;
    hashTable->bucketArray = (Bucket**) malloc(initialCapacity * sizeof(Bucket*));
    for (int i = 0; i < initialCapacity; i++)
    {
        hashTable->bucketArray[i] = NULL;
    }
    return hashTable;
}

Bucket* createBucket(MyString* key, int value)
{
    Bucket* newBucket = (Bucket*) malloc(sizeof(Bucket));
    newBucket->key = cloneString(key);
    newBucket->isDeleted = false;
    newBucket->numberOfAttemptsToInsert = 0;
    newBucket->value = value;
    return newBucket;
}

void deleteBucket(Bucket* bucket)
{
    if (bucket != NULL)
    {
        deleteString(bucket->key);
        free(bucket);
    }
}

void deleteBucketArray(Bucket** bucketArray, int capacityOfBucketArray)
{
    for (int i = 0; i < capacityOfBucketArray; i++)
    {
        deleteBucket(bucketArray[i]);
    }
    free(bucketArray);
}

void deleteHashTable(HashTable* hashTable)
{
    if (hashTable == NULL)
    {
        return;
    }
    deleteBucketArray(hashTable->bucketArray, hashTable->capacity);
    free(hashTable);
}

long int getHash(MyString* key, int base)
{
    long int hash = 0;
    int lengthOfString = getLengthOfString(key);
    char* string = convertStringToCharArray(key);

    for (int i = 0; i < lengthOfString; i++)
    {
        hash = (long int) (((unsigned long long) hash +
                            (unsigned long long) string[i] * (unsigned long long) getPower(primeNumber, i)) % base);
    }
    free(string);
    return hash;
}

Bucket* findBucket(MyString* key, HashTable* hashTable)
{
    if (hashTable == NULL || key == NULL)
    {
        return NULL;
    }

    long int hash = getHash(key, hashTable->capacity);
    int numberOfAttempt = 0;
    Bucket* currentBucket = hashTable->bucketArray[hash];

    while (currentBucket != NULL)
    {
        if (!currentBucket->isDeleted && areStringEqual(key, currentBucket->key))
        {
            return currentBucket;
        }
        numberOfAttempt++;
        hash = (hash + (int) getPower(numberOfAttempt, 2)) % hashTable->capacity;
        currentBucket = hashTable->bucketArray[hash];
    }

    return NULL;
}

bool deleteBucketFromHashTable(MyString* key, HashTable* hashTable)
{
    if (key == NULL || hashTable == NULL)
    {
        return false;
    }

    Bucket* bucket = findBucket(key, hashTable);
    if (bucket == NULL)
    {
        return false;
    }
    bucket->isDeleted = true;
    hashTable->size--;
    return true;
}

bool isInHashTable(MyString* key, HashTable* hashTable)
{
    return findBucket(key, hashTable) != NULL;
}

Bucket* cloneBucket(Bucket* bucket)
{
    Bucket* clonedBucket = (Bucket*) malloc(sizeof(Bucket));
    clonedBucket->key = cloneString(bucket->key);
    clonedBucket->isDeleted = bucket->isDeleted;
    clonedBucket->numberOfAttemptsToInsert = bucket->numberOfAttemptsToInsert;
    clonedBucket->value = bucket->value;
    return clonedBucket;
}

bool addBucketToArray(Bucket* bucket, Bucket** bucketArray, int capacityOfBucketArray)
{
    if (bucket == NULL || bucketArray == NULL)
    {
        return false;
    }

    long int hash = getHash(bucket->key, capacityOfBucketArray);
    int numberOfAttempt = 0;
    Bucket* currentBucket = bucketArray[hash];

    while (currentBucket != NULL && !currentBucket->isDeleted)
    {
        if (areStringEqual(bucket->key, currentBucket->key))
        {
            return false;
        }
        numberOfAttempt++;
        hash = (hash + (int) getPower(numberOfAttempt, 2)) % capacityOfBucketArray;
        currentBucket = bucketArray[hash];
    }

    if (currentBucket != NULL)
    {
        deleteBucket(currentBucket);
    }

    bucket->numberOfAttemptsToInsert = numberOfAttempt;
    bucketArray[hash] = bucket;
    return true;
}


Bucket** getExpendedBucketArray(Bucket** previousBucketArray, int previousCapacity)
{
    int newCapacity = previousCapacity * 2;
    Bucket** newBucketArray = malloc(newCapacity * sizeof(Bucket*));
    Bucket* movedBucket = NULL;
    for (int i = 0; i < newCapacity; i++)
    {
        newBucketArray[i] = NULL;
    }

    for (int i = 0; i < previousCapacity; i++)
    {
        movedBucket = previousBucketArray[i];
        if (movedBucket != NULL && !movedBucket->isDeleted)
        {
            Bucket* newBucket = cloneBucket(previousBucketArray[i]);
            addBucketToArray(newBucket, newBucketArray, newCapacity);
        }
    }

    return newBucketArray;
}

bool expandHashTable(HashTable* hashTable)
{
    if (hashTable == NULL)
    {
        return false;
    }

    int previousCapacity = hashTable->capacity;
    int newCapacity = previousCapacity * 2;
    Bucket** removedBucket = hashTable->bucketArray;
    hashTable->bucketArray = getExpendedBucketArray(removedBucket, previousCapacity);

    hashTable->capacity = newCapacity;


    deleteBucketArray(removedBucket, previousCapacity);

    return true;
}

bool addToHashTable(HashTable* hashTable, MyString* key, int value)
{
    if (key == NULL || hashTable == NULL || isInHashTable(key, hashTable))
    {
        return false;
    }

    Bucket* newBucket = createBucket(key, value);
    addBucketToArray(newBucket, hashTable->bucketArray, hashTable->capacity);
    hashTable->size++;
    double currentLoadFactor = getLoadFactor(hashTable);
    if (currentLoadFactor > hashTable->maxLoadFactor)
    {
        expandHashTable(hashTable);
    }
    return true;
}

double getLoadFactor(HashTable* hashTable)
{
    return (double) hashTable->size / (double) hashTable->capacity;
}

int getValueByKey(MyString* key, HashTable* hashtable)
{
    if (hashtable == NULL || key == NULL)
    {
        return 0;
    }

    Bucket* bucket = findBucket(key, hashtable);
    if (bucket != NULL)
    {
        return bucket->value;
    }

    return 0;
}

bool setValueByKey(HashTable* hashTable, MyString* key, int value)
{
    if (hashTable == NULL || key == NULL)
    {
        return false;
    }
    Bucket* necessaryBucket = findBucket(key, hashTable);
    if (necessaryBucket != NULL)
    {
        necessaryBucket->value = value;
        return true;
    }
    return false;
}

void printBucket(Bucket* printedBucket, FILE* outputStream)
{
    fprintf(outputStream, "\"");
    printString(printedBucket->key, outputStream);
    fprintf(outputStream, "\"; %d", printedBucket->value);
}

bool printHashTable(HashTable* hashTable, FILE* outputStream)
{
    if (hashTable == NULL)
    {
        fprintf(outputStream, "Hash table not initialized.");
        return false;
    }

    Bucket* printedBucket = NULL;
    for (int i = 0; i < hashTable->capacity; i++)
    {
        printedBucket = hashTable->bucketArray[i];
        if (printedBucket != NULL && !printedBucket->isDeleted)
        {
            printBucket(printedBucket, outputStream);
            fprintf(outputStream, "\n");
        }
    }
    return true;
}

bool printHashTableInformation(HashTable* hashTable, FILE* outputStream)
{
    if (hashTable == NULL)
    {
        fprintf(outputStream, "Hash table not initialized.");
        return false;
    }
    fprintf(outputStream, "-------HASH TABLE INFORMATION----------\n");

    Bucket* bucketWithMaxNumberOfProbes = NULL;
    int maxNumberOfProbes = 0;
    double averageNumberOfProbes = 0;
    int totalNumberOfProbes = 0;
    double loadFactor = getLoadFactor(hashTable);
    int numberOfEmptyBuckets = hashTable->capacity - hashTable->size;

    Bucket* currentBucket = NULL;
    for (int i = 0; i < hashTable->capacity; i++)
    {
        currentBucket = hashTable->bucketArray[i];
        if (currentBucket != NULL && !currentBucket->isDeleted)
        {
            if (maxNumberOfProbes < currentBucket->numberOfAttemptsToInsert)
            {
                bucketWithMaxNumberOfProbes = currentBucket;
                maxNumberOfProbes = bucketWithMaxNumberOfProbes->numberOfAttemptsToInsert;
            }
            totalNumberOfProbes += currentBucket->numberOfAttemptsToInsert;
        }
    }
    if (hashTable->size != 0)
    {
        averageNumberOfProbes = (double) totalNumberOfProbes / (double) hashTable->size;
    }

    fprintf(outputStream, "The number of elements in the hash table: %d\n", hashTable->size);
    fprintf(outputStream, "Number of empty buckets: %d\n", numberOfEmptyBuckets);
    fprintf(outputStream, "Load factor: %lf\n", loadFactor);
    fprintf(outputStream, "Average number of probes: %lf\n", averageNumberOfProbes);
    if (bucketWithMaxNumberOfProbes != NULL)
    {
        fprintf(outputStream, "Maximum number of probes: %d (key: ",
                bucketWithMaxNumberOfProbes->numberOfAttemptsToInsert);
        printString(bucketWithMaxNumberOfProbes->key, outputStream);
        fprintf(outputStream, ")\n");
    }
    else
    {
        fprintf(outputStream, "There isn't the element with the maximum number of probes\n");
    }
    return true;
}



