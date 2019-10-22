#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void swapInteger(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapDouble(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

struct Fraction
{
    int numerator;
    int denominator;
    double value;
};

void swapFraction(struct Fraction* a, struct Fraction* b)
{
    swapInteger(&(a->denominator), &(b->denominator));
    swapInteger(&(a->numerator), &(b->numerator));
    swapDouble(&(a->value), &(b->value));
}

void getCoprimeIntegers(bool isCoprimeIntegers[], int number)
{
    int sizeOfArray = number;

    int halfOfNumber = (int)number / 2;
    for (int factor = 2; factor <= halfOfNumber; factor++)
    {
        if (number % factor == 0)
        {
            for (int indexOfNonCoprime = factor; indexOfNonCoprime < sizeOfArray; indexOfNonCoprime += factor)
            {
                isCoprimeIntegers[indexOfNonCoprime] = false;
            }

            do
            {
                number /= factor;
            } while (number % factor == 0);
        }
    }
}

struct Fraction* getIrreducibleFraction(int maxDenominator, int* numberOfIrreducibleFractions)
{
    int maxNumberOfFractions = (maxDenominator * (maxDenominator + 1)) / 2;
    struct Fraction* irreducibleFractions = (struct Fraction*) malloc(maxNumberOfFractions * sizeof(struct Fraction));

    bool* isCoprimeIntegers = (bool*) malloc(maxDenominator * sizeof(bool));
    isCoprimeIntegers[0] = false;

    for (int i = 0; i < maxDenominator; i++)
    {
        isCoprimeIntegers[i] = true;
    }

    *numberOfIrreducibleFractions = 0;
    for (int denominator = 2; denominator <= maxDenominator; denominator++)
    {
        getCoprimeIntegers(isCoprimeIntegers, denominator);
        for (int numerator = 1; numerator < denominator; numerator++)
        {
            if (isCoprimeIntegers[numerator])
            {
                irreducibleFractions[*numberOfIrreducibleFractions].denominator = denominator;
                irreducibleFractions[*numberOfIrreducibleFractions].numerator = numerator;
                irreducibleFractions[*numberOfIrreducibleFractions].value = (double)numerator / (double)denominator;
                (*numberOfIrreducibleFractions)++;
            }
            else
            {
                isCoprimeIntegers[numerator] = true;
            }
        }
    }

    free(isCoprimeIntegers);
    return irreducibleFractions;
}

void quickSort(struct Fraction array[], int leftElement, int rightElement)
{
    if (rightElement - leftElement < 1)
    {
        return;
    }

    int upIterator = leftElement;
    int downIterator = rightElement;
    int middleIndex = (leftElement + rightElement) / 2;
    double middle = array[middleIndex].value;

    while (upIterator < downIterator)
    {
        while (array[upIterator].value < middle)
        {
            upIterator++;
        }

        while (array[downIterator].value > middle)
        {
            downIterator--;
        }

        if (upIterator <= downIterator)
        {
            swapFraction(&array[upIterator], &array[downIterator]);
            upIterator++;
            downIterator--;
        }
    }

    quickSort(array, upIterator, rightElement);
    quickSort(array, leftElement, downIterator);
}

int main()
{
    int numberOfFractions = 0;
    int maxDenominator = 0;
    printf("Enter maximum denominator from 2:" );
    scanf("%d", &maxDenominator);

    struct Fraction* fractions = getIrreducibleFraction(maxDenominator, &numberOfFractions);

    quickSort(fractions, 0, numberOfFractions - 1);

    printf("All irreducible fractions whose denominators do not exceed %d. They printed in ascending order: \n", maxDenominator);
    for (int i = 0; i < numberOfFractions; i++)
    {
        printf("%d / %d\n", fractions[i].numerator, fractions[i].denominator);
    }

    free(fractions);

    return 0;
}