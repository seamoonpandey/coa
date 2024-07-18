#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToBinary(int n, int *binary, int size)
{
    int negative = n < 0;
    if (negative)
        n = -n;
    for (int i = size - 1; i >= 0; i--)
    {
        binary[i] = n & 1;
        n >>= 1;
    }
    if (negative)
    {
        for (int i = 0; i < size; i++)
        {
            binary[i] = ~binary[i] & 1;
        }
        int carry = 1;
        for (int i = size - 1; i >= 0; i--)
        {
            binary[i] += carry;
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
}

void addBinary(int *a, const int *b, int size)
{
    int carry = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        int sum = a[i] + b[i] + carry;
        a[i] = sum % 2;
        carry = sum / 2;
    }
}

void subtractBinary(int *a, const int *b, int size)
{
    int *negB = (int *)malloc(size * sizeof(int));
    memcpy(negB, b, size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        negB[i] = ~negB[i] & 1;
    }
    int carry = 1;
    for (int i = size - 1; i >= 0; i--)
    {
        negB[i] += carry;
        if (negB[i] == 2)
        {
            negB[i] = 0;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
    addBinary(a, negB, size);
    free(negB);
}

void shiftLeft(int *a, int *q, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        a[i] = a[i + 1];
    }
    a[size - 1] = q[0];
    for (int i = 0; i < size - 1; i++)
    {
        q[i] = q[i + 1];
    }
    q[size - 1] = 0;
}

void printBinary(const int *binary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", binary[i]);
    }
}

int main()
{
    int dividend, divisor;
    printf("Enter dividend: ");
    scanf("%d", &dividend);
    printf("Enter divisor: ");
    scanf("%d", &divisor);

    int size = 32;
    int *A = (int *)calloc(size, sizeof(int));
    int *Q = (int *)malloc(size * sizeof(int));
    int *M = (int *)malloc(size * sizeof(int));

    decimalToBinary(dividend, Q, size);
    decimalToBinary(divisor, M, size);

    int count = size;

    while (count > 0)
    {
        shiftLeft(A, Q, size);
        if (A[0] == 0)
        {
            subtractBinary(A, M, size);
        }
        else
        {
            addBinary(A, M, size);
        }
        Q[size - 1] = A[0] == 0 ? 1 : 0;
        count--;
    }

    if (A[0] != 0)
    {
        addBinary(A, M, size);
    }

    printf("Quotient: ");
    printBinary(Q, size);
    printf("\nRemainder: ");
    printBinary(A, size);
    printf("\n");

    free(A);
    free(Q);
    free(M);

    return 0;
}
