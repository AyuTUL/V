// Lab 2.1: WAP to find Fibonacci sequence of given term using iterative method (ASCII Table)
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void printBorder()
{
    cout << "+-------------+----------+----------+--------+" << endl;
}

void printTableHeader()
{
    printBorder();
    cout << "|  Iteration  |  f(n-2)  |  f(n-1)  |  f(n)  |" << endl;
    printBorder();
}

void printTableRow(int iteration, int i, int f1, int f2, int fn)
{
    cout << "|      " << setw(7) << left << iteration
         << "|    " << setw(6) << left << f1
         << "|    " << setw(6) << left << f2
         << "|   " << setw(5) << left << fn << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

void fibonacci(int n)
{
    int f1 = 0, f2 = 1, fn;

    cout << endl;
    printTableHeader();

    for (int i = 1; i <= n; i++)
    {
        fn = f1;

        printTableRow(i, i, f1, f2, fn);

        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }

    printTableFooter();
}

int main()
{
    int n;

    cout << "Enter nth term of Fibonacci sequence : ";
    cin >> n;
    cout << endl
         << "---Fibonacci Sequence using Iterative Method---" << endl;
    if (n <= 0)
    {
        cout << endl
             << "Invalid input";
        exit(0);
    }

    fibonacci(n);

    return 0;
}
