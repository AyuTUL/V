// Lab 3.2: Fibonacci using Recursion with ASCII Trace Table
#include <iostream>
#include <iomanip>
using namespace std;

int call = 0;

int fibonacci(int n)
{
    call++;
    int currentCall = call;

    // Print function call
    cout << "| Call " << currentCall << " | fibonacci(" << n << ") | ";

    if (n <= 1)
    {
        cout << "Return " << n << " |\n";
        return n;
    }

    int result = fibonacci(n - 1) + fibonacci(n - 2);

    // Print return value
    cout << "| Call " << currentCall << " | fibonacci(" << n << ") | Return " << result << " |\n";

    return result;
}

int main()
{
    int n;
    cout << "--- Fibonacci Using Recursive Method (ASCII Table) ---\n";
    cout << "Enter nth term: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid input\n";
    }
    else
    {
        cout << "\n---------------------------------------------\n";
        cout << "| Call No | Function Call | Return Value |\n";
        cout << "---------------------------------------------\n";

        int result = fibonacci(n);

        cout << "---------------------------------------------\n";
        cout << "\nFibonacci(" << n << ") = " << result << endl;
    }

    return 0;
}
