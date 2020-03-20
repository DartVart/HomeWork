#include <stdio.h>

int getRecursiveFactorial(int number)
{
    return (number == 0) ? 1 : getRecursiveFactorial(number - 1) * number;
}

int getIterativeFactorial(int number)
{
    int result = 1;

    for (int i = 2; i <= number; i++)
    {
        result *= i;
    }

    return result;
}


int main(int argc, char* argv[])
{
    int inputNumber = 0;
    printf("Enter a positive integer up to 13: ");
    scanf("%d", &inputNumber);

    printf("%d! = %d (The factorial calculated recursively)\n", inputNumber, getRecursiveFactorial(inputNumber));
    printf("%d! = %d (The factorial calculated iteratively)", inputNumber, getIterativeFactorial(inputNumber));

    return 0;
}