// Lab 2: WAP to implement Euclid’s algorithm to find GCD of two numbers.
#include <iostream>
#include <iomanip>
using namespace std;

void printBorder()
{
    cout << "+-------------+--------+--------+-------------+" << endl;
}

void printTableHeader()
{
    printBorder();
    cout << "|  Iteration  |   a    |   b    |  r = a % b  |" << endl;
    printBorder();
}

void printTableRow(int iteration, int a, int b, int r)
{
    cout << "|      " << setw(7) << left << iteration
         << "|  " << setw(6) << left << a
         << "|  " << setw(6) << left << b
         << "|     " << setw(8) << left << r << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

int gcd(int a, int b)
{
    int r, i = 1;

    cout << endl;
    printTableHeader();

    if (b == 0)
    {
        printTableRow(i, a, b, 0);
        printTableFooter();
        return a;
    }

    while (b != 0)
    {
        r = a % b;
        printTableRow(i, a, b, r);
        a = b;
        b = r;
        i++;
    }

    printTableFooter();
    return a;
}
int main()
{
    int a, b;

    cout << "Enter 2 numbers : ";
    cin >> a >> b;
    cout << endl
         << "---GCD using Euclidean Algorithm---" << endl;
    if (a < 0 || b < 0)
    {
        cout << endl
             << "GCD of negative numbers doesn't exist.";
        return 0;
    }
    if (a == 0 && b == 0)
    {
        cout << endl
             << "GCD of both 0 doesn't exist.";
        return 0;
    }

    int result = gcd(a, b);

    cout << endl
         << "Final Result : GCD(" << a << "," << b << ") = " << result;
    return 0;
}