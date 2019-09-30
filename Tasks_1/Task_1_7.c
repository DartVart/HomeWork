#include <stdio.h>
#include <math.h>
#include <stdbool.h>

const int maxSizeOfArray = 10001;

void getPrimes(bool sieveOfEratosthenes[], int maxNumber)
{
    sieveOfEratosthenes[0] = false;
    sieveOfEratosthenes[1] = false;

    int squareRootOfMaxNumber = (int)sqrt(maxNumber);
    for (int i = 2; i <= squareRootOfMaxNumber; i++)
    {
        for (int indexOfNonPrime = i * i; indexOfNonPrime <= maxNumber; indexOfNonPrime += i)
        {
            sieveOfEratosthenes[indexOfNonPrime] = false;
        }
    }
}

// Output: "2 3 5 ..."
void printPrimes(bool sieveOfEratosthenes[], int sizeOfSieveAsArray)
{
    for (int i = 0; i < sizeOfSieveAsArray; i++)
    {
        if (sieveOfEratosthenes[i])
        {
            printf("%d ", i);
        }
    }
}

int main(int argc, char* argv[])
{

    int inputNumber = 0;
    printf("Enter an integer from 2 to %d : ", maxSizeOfArray - 1);
    scanf("%d", &inputNumber);

    bool sieveOfEratosthenes[maxSizeOfArray];

    for (int i = 0; i <= inputNumber; i++)
    {
        sieveOfEratosthenes[i] = true;
    }

    getPrimes(sieveOfEratosthenes, inputNumber);

    printf("All prime numbers not exceeding %d: ", inputNumber);
    printPrimes(sieveOfEratosthenes, inputNumber + 1);

    return 0;
}