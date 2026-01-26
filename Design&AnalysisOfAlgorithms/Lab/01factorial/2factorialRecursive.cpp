// Lab 1.2: WAP to compute factorial of a number using recursive method.
#include <iostream>
#include <iomanip>
using namespace std;

int callDepth = 0;
int borderWidth = 0; // Store original input for consistent table width

void printBorder()
{
    cout << "+----------+---------+";
    for (int i = 0; i < (borderWidth + 7); i++)
        cout << "-";
    cout << "+";
    for (int i = 0; i < (borderWidth + 2); i++)
        cout << "-";
    cout << "+" << endl;
}

void printTableHeader()
{
    cout << endl;
    printBorder();
    cout << "|  Action  |  Depth  |  " << setw(borderWidth + 5) << left << "Stack Trace" << "|  " << setw(borderWidth) << left << "Result" << "|" << endl;
    printBorder();
}

void printTableRow(string action, int depth, string trace, string result)
{
    cout << "|  " << setw(8) << left << action
         << "|    " << setw(5) << left << depth
         << "|  " << setw(borderWidth + 5) << left << trace
         << "|  " << setw(borderWidth) << left << result << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

void printStack(int n, bool isCall, int multiplier = 0, int subResult = 0)
{
    string indent = "";
    for (int i = 1; i < callDepth; i++)
        indent += "  ";

    if (isCall)
    {
        string trace = indent + "--> fact(" + to_string(n) + ")";
        printTableRow("CALL", callDepth, trace, "-");
    }
    else
    {
        string trace = indent + "<-- ";
        string result;
        if (multiplier > 0)
            result = to_string(multiplier) + " x " + to_string(subResult) + " = " + to_string(n);
        else
            result = to_string(n);
        printTableRow("RETURN", callDepth, trace, result);
    }
}

int fact(int n)
{
    callDepth++;
    printStack(n, true);

    int result;
    if (n <= 1)
    {
        result = 1;
        printStack(result, false);
    }
    else
    {
        int subResult = fact(n - 1);
        result = n * subResult;
        printStack(result, false, n, subResult);
    }

    callDepth--;
    return result;
}
int main()
{
    int n;

    cout << "Enter number : ";
    cin >> n;
    cout << endl
         << "---Factorial using Recursive Method---" << endl;
    if (n < 0)
    {
        cout << endl
             << "Factorial of negative number doesn't exist.";
        return 0;
    }

    borderWidth = n * 2 + 8;
    printTableHeader();

    int result = fact(n);

    printTableFooter();
    cout << endl
         << "Final Result : " << n << "! = " << result;
    return 0;
}