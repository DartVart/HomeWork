#include <stdio.h>

int getFibonacciNumber(int sequenceNumber)
{
    int previousFibonacciNumber = 0;
    int fibonacciNumber = 1;

    if (sequenceNumber == 0)
    {
        return 0;
    }

    for (int i = 0; i < sequenceNumber - 1; i++)
    {
        fibonacciNumber += previousFibonacciNumber;
        previousFibonacciNumber = fibonacciNumber - previousFibonacciNumber;
    }

    return fibonacciNumber;
}

int main()
{
    int fibonacciSequenceNumber = 0;
    printf("Enter number (i), which means the number in the sequence of Fibonacci numbers: ");
    scanf("%d", &fibonacciSequenceNumber);
    int requiredFibonacciNumber = getFibonacciNumber(fibonacciSequenceNumber);
    printf ("The number having the number %d in the Fibonacci sequence: %d", fibonacciSequenceNumber, requiredFibonacciNumber);
    return 0;
}