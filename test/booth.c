#include <stdio.h>
#include <stdint.h>

void printBinary(int32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

void printRow(int count, int32_t accumulator, int32_t q, int a, const char *operation) {
    printBinary(accumulator);
    printf(" | ");
    printBinary(q);
    printf(" |   %d   |   %d   | %s\n", a, count, operation);
}

int main() {
    int32_t x, y, a = 0, count = 32;

    printf("Enter the first number: ");
    scanf("%d", &x);
    printf("Enter the second number: ");
    scanf("%d", &y);

    int32_t first = x;
    int32_t second = y;
    int32_t accumulator = 0;
    int32_t complementSecond = ~second + 1;  // Two's complement of second

    printf("First number in binary: ");
    printBinary(first);
    printf("\n");

    printf("Second number in binary: ");
    printBinary(second);
    printf("\n\n");

    int32_t q = first;

    printf("|             A             |             Q             | Q-1 | COUNT | Remarks\n");
    printf("|---------------------------|---------------------------|-----|-------|---------------------------\n");

    printRow(count, accumulator, q, a, "Initialization");

    while (count > 0) {
        if ((q & 1) == 0 && a == 1) {
            accumulator += second;
            printRow(count, accumulator, q, a, "Q[0]Q-1=10\tAddition A=A+M");
        } else if ((q & 1) == 1 && a == 0) {
            accumulator += complementSecond;
            printRow(count, accumulator, q, a, "Q[0]Q-1=01\tSubtraction A=A-M");
        }

        a = q & 1;
        q = (q >> 1) | ((accumulator & 1) << 31);
        accumulator >>= 1;
        if (accumulator & (1 << 31)) {  // Preserve the sign bit for accumulator
            accumulator |= (1 << 31);
        }
        count--;
        printRow(count, accumulator, q, a, "Arithmetic Right Shift A Q Q-1");
        printf("\n");
    }

    printf("Result after Booth's multiplication:\n");
    printBinary(accumulator);
    printBinary(q);
    printf("\n");

    return 0;
}

