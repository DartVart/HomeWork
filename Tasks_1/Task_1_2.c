#include <stdio.h>

int integerDivision(int dividend, int divisor)
{
    int result = 0;

    while (dividend >= divisor)
    {
        dividend -= divisor;
        result++;
    }

    return result;
}



int main(int argc, char* argv[])
{
    int dividend, divisor;
    printf("Enter two positive integers (the dividend and the divisor): ");
    scanf("%d%d", &dividend, &divisor);

    printf("Integer division of these numbers: %d", integerDivision(dividend, divisor));

    return 0;
}