// Lab 1.1: WAP to compute factorial of a number using iterative method.
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int borderWidth = 0; // Store original input for consistent table width

void printBorder()
{
    cout << "+-------------+-----+";
    for (int i = 0; i < (borderWidth * 2) + 13; i++)
        cout << "-";
    cout << "+" << endl;
}

void printTableHeader()
{
    printBorder();
    cout << "|  Iteration  |  i  |  " << setw((borderWidth * 2) + 11) << left << "Factorial" << "|" << endl;
    printBorder();
}

void printTableRow(int iteration, int i, string factStr)
{
    cout << "|      " << setw(7) << left << iteration << "|  " << left << setw(3) << i << "|  " << setw((borderWidth * 2) + 11) << left << factStr << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

int factorial(int n)
{
    int fact = 1, iteration = 1;
    string operation = "";

    cout << endl;
    printTableHeader();

    if (n == 0)
        printTableRow(iteration, 0, "1");
    else
        for (int i = n; i >= 1; i--)
        {
            fact *= i;

            // Build operation string
            if (operation.empty())
            {
                operation = to_string(i);
                printTableRow(iteration, i, operation);
            }
            else
            {
                operation = operation + "x" + to_string(i);
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

    borderWidth = n;
    int result = factorial(n);

    cout << endl
         << "Final Result : " << n << "! = " << result;
    return 0;
}