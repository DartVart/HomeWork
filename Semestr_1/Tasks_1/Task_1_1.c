#include <stdio.h>

int main(int argc, char* argv[])
{
    double inputX = 0.0;
    printf("Enter real number (x): ");
    scanf("%lf", &inputX);

    double squareOfX = inputX * inputX;
    printf("x^4 + x^3 + x^2 + x^1 + x + 1 = %lf", (squareOfX + 1) * (squareOfX + inputX) + 1);

    return 0;
}