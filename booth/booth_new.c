#include <stdio.h>
#include <stdbool.h>


void printBinary(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void arithmeticRightShift(int *A, int *Q, bool *a, int n) {
    bool signA = *A < 0;
    *a = (*Q & 1);
    *Q = (*Q >> 1) | ((*A & 1) << (n - 1));
    *A = (*A >> 1);
    if (signA) {
        *A |= (1 << (n - 1));
    }
}

void boothMultiplication(int M, int Q, int n) {
    int mc = (~M + 1);
    int A = 0; bool a = 0;
    int count = n;

    while (count > 0) {
        printf("Step %d:\n", n - count);
        printf("A = "); printBinary(A, n); printf("Q = "); printBinary(Q, n); printf("a = %d\n\n", a);

        if ((Q & 1) == 1 && a == 0) {
            A += mc;
        } else if ((Q & 1) == 0 && a == 1) {
            A += M;
        }

        arithmeticRightShift(&A, &Q, &a, n);
        count--;
    }

    printf("Final Result:\n");
    printf("A = "); printBinary(A, n); printf("Q = "); printBinary(Q, n);
}

int main() {
    int M , Q , n;
    printf("Enter the number M and Q and number of bits");
    scanf("%d %d %d", &M, &Q, &n);
    boothMultiplication(M, Q, n);
    return 0;
}

