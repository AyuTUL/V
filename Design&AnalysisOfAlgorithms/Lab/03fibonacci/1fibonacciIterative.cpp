// Lab 3.1: WAP to find Fibonacci sequence of given term using iterative method (ASCII Table)
#include <iostream>
#include <iomanip>
using namespace std;

int borderWidth = 0;

void printBorder()
{
    cout << "+-------------+-------+----------+----------+";
    for (int i = 0; i < (borderWidth + 2); i++)
        cout << "-";
    cout << "+" << endl;
}

void printTableHeader()
{
    printBorder();
    cout << "|  Iteration  |   i   |  f(n-2)  |  f(n-1)  |  " << setw(borderWidth) << left << "f(n)" << "|" << endl;
    printBorder();
}

void printTableRow(int iteration, int i, int f1, int f2, string fn)
{
    cout << "|      " << setw(7) << left << iteration
         << "|   " << setw(4) << left << i
         << "|    " << setw(6) << left << f1
         << "|    " << setw(6) << left << f2
         << "|  " << setw(borderWidth) << left << fn << "|" << endl;
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

    for (int i = 1; i <= n - 2; i++)
    {
        fn = f1 + f2;
        string fnStr = to_string(f1) + "+" + to_string(f2) + "=" + to_string(fn);

        printTableRow(i, i + 2, f1, f2, fnStr);

        f1 = f2;
        f2 = fn;
    }

    printTableFooter();

    cout << endl
         << "The " << n << "th Fibonacci number is : " << f2;
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
        return 0;
    }

    borderWidth = n + 6;
    fibonacci(n);

    return 0;
}