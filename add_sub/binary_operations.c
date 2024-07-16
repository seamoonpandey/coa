#include "binary_operations.h"
#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n, int *binary, int size)
{
    if (n < 0)
    {
        n = abs(n);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        binary[i] = n % 2;
        n = n / 2;
    }
}

void twosComplement(int *binary, int size)
{
    int carry = 1;

    for (int i = 0; i < size; i++)
    {
        binary[i] = binary[i] == 0 ? 1 : 0;
    }

    for (int i = size - 1; i >= 0; i--)
    {
        binary[i] = binary[i] + carry;
        if (binary[i] == 2)
        {
            binary[i] = 0;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}

void printBinary(int *binary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", binary[i]);
    }
    printf("\n");
}

void addTwoBinaries(int *binary1, int *binary2, int size)
{
    int carry = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        binary1[i] = binary1[i] + binary2[i] + carry;
        if (binary1[i] == 2)
        {
            binary1[i] = 0;
            carry = 1;
        }
        else if (binary1[i] == 3)
        {
            binary1[i] = 1;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}
