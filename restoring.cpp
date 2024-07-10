#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

void printBinary(int value, int bits)
{
    for (int i = bits - 1; i >= 0; --i)
    {
        cout << ((value >> i) & 1);
    }
}

int toTwosComplement(int value, int bits)
{
    if (value < 0)
    {
        value = (1 << bits) + value;
    }
    return value;
}

int main()
{
    int dividend, divisor;
    cout << "Enter dividend: ";
    cin >> dividend;
    cout << "Enter divisor: ";
    cin >> divisor;

    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1; // Determine the sign of the result

    int bits = sizeof(int); // Number of bits in an integer (corrected to multiply by 8)

    dividend = toTwosComplement(dividend, bits);
    divisor = toTwosComplement(divisor, bits);

    int quotient = 0, remainder = 0;
    int max_value = (1 << bits) - 1; // 1111... for negative handling

    // Header for the table
    cout << setw(5) << "Step" << setw(20) << "Quotient" << setw(20) << "Remainder" << setw(40) << "Action" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    for (int i = bits - 1; i >= 0; --i)
    {
        cout << setw(5) << (bits - i);

        remainder = (remainder << 1) | ((dividend >> i) & 1); // Shift left and bring down next bit
        quotient <<= 1;                                       // Shift quotient left

        cout << setw(20);
        printBinary(quotient, bits);

        cout << setw(20);
        printBinary(remainder, bits);

        cout << setw(40) << "Shift Left and Bring Down" << endl;

        remainder -= divisor; // Subtract divisor

        cout << setw(5) << " "
             << setw(20);
        printBinary(quotient, bits);
        cout << setw(20);
        printBinary(remainder, bits);

        if (remainder & (1 << (bits - 1)))
        {                         // Check if remainder is negative
            remainder += divisor; // Restore original remainder
            cout << setw(40) << "Restore Remainder" << endl;
        }
        else
        {
            quotient |= 1; // Set current quotient bit to 1
            cout << setw(40) << "Set Quotient Bit" << endl;
        }
    }

    quotient *= sign; // Apply the sign to the quotient
    if (sign == -1)
    {
        remainder = max_value - remainder + 1; // Convert remainder to two's complement if the result is negative
    }

    cout << "Quotient: " << quotient << endl;
    cout << "Remainder: " << remainder << endl;

    return 0;
}
