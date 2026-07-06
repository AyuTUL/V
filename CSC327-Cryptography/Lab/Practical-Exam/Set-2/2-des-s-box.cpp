// Q 2.2: Demonstrate the working of a DES S-Box by accepting a 6-bit binary input, determining the row and column values, and producing the corresponding 4-bit output using any selected DES S-Box.
#include <bits/stdc++.h>
using namespace std;

// Lab 8: DES S-Box substitution demonstration
// - Input: 6-bit binary string (b0 b1 b2 b3 b4 b5)
// - Row formed from outer bits: b0 and b5
// - Column formed from middle 4 bits: b1..b4
// - Output: 4-bit binary (DES S-box value)
int main()
{
    const int S1[4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

    string bits;
    cout << "Enter 6-bit input : ";
    cin >> bits;

    if (bits.length() != 6)
        return cout << "Invalid input: need exactly 6 bits\n", 0;
    for (char c : bits)
        if (c != '0' && c != '1')
            return cout << "Invalid input: only characters '0' or '1' allowed", 0;

    int row = (bits[0] - '0') * 2 + (bits[5] - '0');
    int col = (bits[1] - '0') * 8 + (bits[2] - '0') * 4 +
              (bits[3] - '0') * 2 + (bits[4] - '0');

    int value = S1[row][col];
    string output = bitset<4>(value).to_string();

    cout << endl
         << "Row = " << row << endl
         << "Column = " << col << endl
         << "Decimal Output = " << value << endl
         << "4-bit Output = " << output;

    return 0;
}