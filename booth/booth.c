#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void decimalToBinary(int n, int *binary, int size)
{
    n = abs(n);
    for (int i = size - 1; i >= 0; i--)
    {
        binary[i] = n & 1;
        n >>= 1;
    }
}

void twosComplement(int *binary, int size)
{
    int carry = 1;

    for (int i = 0; i < size; i++)
    {
        binary[i] = ~binary[i] & 1;
    }

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

void arithmeticRightShift(int *binary1, int *binary2, int *a, int size)
{
    *a = binary2[size - 1];

    for (int i = size - 1; i > 0; i--)
    {
        binary2[i] = binary2[i - 1];
    }

    binary2[0] = binary1[size - 1];

    int msb = binary1[0];
    for (int i = size - 1; i > 0; i--)
    {
        binary1[i] = binary1[i - 1];
    }
    binary1[0] = msb;
}

void addTwoBinaries(int *binary1, const int *binary2, int size)
{
    int carry = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        int sum = binary1[i] ^ binary2[i] ^ carry;
        carry = (binary1[i] & binary2[i]) | (binary2[i] & carry) | (carry & binary1[i]);
        binary1[i] = sum;
    }
}

void printBinary(const int *binary, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", binary[i]);
    }
}

void printRow(int count, const int *accumulator, const int *temp, int a, const char *operation, int size)
{
    printBinary(accumulator, size);
    printf(" | ");
    printBinary(temp, size);
    printf(" |   %d   |   %d   | %s\n", a, count, operation);
}

int main()
{
    int x, y, a = 0, count;
    int size;

    printf("Enter the size: ");
    scanf("%d", &size);

    int *first = (int *)malloc(size * sizeof(int));
    int *second = (int *)malloc(size * sizeof(int));
    int *accumulator = (int *)calloc(size, sizeof(int));
    int *complementSecond = (int *)malloc(size * sizeof(int));
    int *temp = (int *)malloc(size * sizeof(int));

    printf("Enter the first number: ");
    scanf("%d", &x);
    printf("Enter the second number: ");
    scanf("%d", &y);

    decimalToBinary(x, first, size);
    if (x < 0)
    {
        twosComplement(first, size);
    }
    printf("First number in binary: ");
    printBinary(first, size);
    printf("\n");

    decimalToBinary(y, second, size);
    if (y < 0)
    {
        twosComplement(second, size);
    }
    printf("Second number in binary: ");
    printBinary(second, size);
    printf("\n\n");

    for (int i = 0; i < size; i++)
    {
        complementSecond[i] = second[i];
    }

    twosComplement(complementSecond, size);

    for (int i = 0; i < size; i++)
    {
        temp[i] = first[i];
    }

    count = size;
    printf("|   A   |   Q   | Q-1 | COUNT | Remarks\n");
    printf("|-------|-------|-----|-------|-----------\n");

    printRow(count, accumulator, temp, a, "Initialization", size);

    while (count > 0)
    {
        if ((temp[size - 1] == 0) && (a == 1))
        {
            addTwoBinaries(accumulator, second, size);
            printRow(count, accumulator, temp, a, "Q[0]Q-1=10\tAddition A=A+M", size);
            arithmeticRightShift(accumulator, temp, &a, size);
            count--;
            printRow(count, accumulator, temp, a, "Arithematic Right Shift A Q Q-1", size);
            printf("\n");
        }
        else if ((temp[size - 1] == 1) && (a == 0))
        {
            addTwoBinaries(accumulator, complementSecond, size);
            printRow(count, accumulator, temp, a, "Q[0]Q-1=01\tSubtraction A=A-M", size);
            arithmeticRightShift(accumulator, temp, &a, size);
            count--;
            printRow(count, accumulator, temp, a, "Arithematic Right Shift A Q Q-1", size);
            printf("\n");
        }
        else
        {
            arithmeticRightShift(accumulator, temp, &a, size);
            count--;
            printRow(count, accumulator, temp, a, "Arithematic Right Shift A Q Q-1", size);
            printf("\n");
        }
    }

    printf("Result after Booth's multiplication:\n");
    printBinary(accumulator, size);
    printBinary(temp, size);
    printf("\n");

    free(first);
    free(second);
    free(accumulator);
    free(complementSecond);
    free(temp);

    return 0;
}
