// Lab 1.1: WAP to compute factorial of a number using iterative method.
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int borderWidth = 0;

void printBorder()
{
    cout << "+-------------+-----+";
    for (int i = 0; i < (borderWidth + 2); i++)
        cout << "-";
    cout << "+" << endl;
}

void printTableHeader()
{
    printBorder();
    cout << "|  Iteration  |  i  |  " << setw(borderWidth) << left << "Factorial" << "|" << endl;
    printBorder();
}

void printTableRow(int iteration, int i, string factStr)
{
    cout << "|      " << setw(7) << left << iteration << "|  " << left << setw(3) << i << "|  " << setw(borderWidth) << left << factStr << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

unsigned long long factorial(int n)
{
    unsigned long long fact = 1;
    int iteration = 1;
    string operation = "";

    cout << endl;
    printTableHeader();

    if (n == 0)
        printTableRow(iteration, 0, "1");
    else
        for (int i = n; i >= 1; i--)
        {
            fact *= i;
            if (operation.empty())
            {
                operation = to_string(i);
                printTableRow(iteration, i, operation);
            }
            else
            {
                operation = operation + " x " + to_string(i);
                string factStr = operation + " = " + to_string(fact);
                printTableRow(iteration, i, factStr);
            }
            iteration++;
        }

    printTableFooter();
    return fact;
}

int main()
{
    int n;
    cout << "Enter number : ";

    cin >> n;
    cout << endl
         << "---Factorial using Iterative Method---" << endl;
    if (n < 0)
    {
        cout << endl
             << "Factorial of negative number doesn't exist.";
        exit(0);
    }

    borderWidth = n * 5 + 11;
    unsigned long long result = factorial(n);

    cout << endl
         << "Final Result : " << n << "! = " << result;
    return 0;
}