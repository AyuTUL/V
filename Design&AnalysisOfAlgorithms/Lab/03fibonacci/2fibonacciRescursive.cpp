// Lab 3.2: Fibonacci using Recursion with ASCII Trace Table (Like Factorial)
#include <iostream>
#include <iomanip>
using namespace std;

int callDepth = 0;
int borderWidth = 0;

void printBorder()
{
    cout << "+----------+---------+";
    for (int i = 0; i < (borderWidth + 7); i++)
        cout << "-";
    cout << "+----------+" << endl;
}

void printTableHeader()
{
    cout << endl;
    printBorder();
    cout << "|  Action  |  Depth  |  " << setw(borderWidth + 5) << left << "Stack Trace"
         << "|  Result  |" << endl;
    printBorder();
}

void printTableRow(string action, int depth, string trace, string result)
{
    cout << "|  " << setw(8) << left << action
         << "|    " << setw(5) << left << depth
         << "|  " << setw(borderWidth + 5) << left << trace
         << "|    " << setw(6) << left << result << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

void printStack(int n, bool isCall, int res = -1)
{
    string indent = "";
    for (int i = 1; i < callDepth; i++)
        indent += "  ";

    if (isCall)
    {
        string trace = indent + "--> fib(" + to_string(n) + ")";
        printTableRow("CALL", callDepth, trace, "-");
    }
    else
    {
        string trace = indent + "<-- ";
        string result = to_string(res);
        printTableRow("RETURN", callDepth, trace, result);
    }
}

int fibonacciRecursive(int n)
{
    callDepth++;
    printStack(n, true);

    int result;

    if (n <= 1)
    {
        result = n;
        printStack(n, false, result);
    }
    else
    {
        int a = fibonacciRecursive(n - 1);
        int b = fibonacciRecursive(n - 2);
        result = a + b;
        printStack(n, false, result);
    }

    callDepth--;
    return result;
}

int main()
{
    int n;

    cout << "Enter nth term of Fibonacci sequence : ";
    cin >> n;
    cout << endl
         << "---Fibonacci Sequence using Recursive Method---" << endl;
    if (n <= 0)
    {
        cout << endl
             << "Invalid input";
        return 0;
    }

    borderWidth = n * 3 + 5;
    printTableHeader();
    int result = fibonacciRecursive(n);
    printTableFooter();

    cout << endl
         << "The " << n << "th Fibonacci number is : " << result;
    return 0;
}
