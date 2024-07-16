#include <stdio.h>
#include "binary_operations.h"

int main()
{
    int a1, b1, a[SIZE], b[SIZE];

    printf("Enter the first number: ");
    scanf("%d", &a1);
    printf("Enter the second number: ");
    scanf("%d", &b1);
    printf("\n");

    decimalToBinary(a1, a, SIZE);
    if (a1 < 0)
    {
        twosComplement(a, SIZE);
    }

    printf("First number in binary: ");
    printBinary(a, SIZE);

    decimalToBinary(b1, b, SIZE);
    if (b1 < 0)
    {
        twosComplement(b, SIZE);
    }

    printf("Second number in binary: ");
    printBinary(b, SIZE);
    printf("\n");

    int sum[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        sum[i] = a[i];
    }
    addTwoBinaries(sum, b, SIZE);

    printf("Sum of the given two numbers: ");
    printBinary(sum, SIZE);

    return 0;
}
