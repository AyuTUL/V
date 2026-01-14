// Lab 1.1: WAP to find Fibonacci sequence of given term using iterative method.
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
    int n, f1 = 0, f2 = 1, fn = 0;
    cout << "---Fibonacci Sequence using Iterative Method---" << endl;
    cout << "Enter nth term of Fibonacci sequence : ";
    cin >> n;
    if (n <= 0)
        cout << endl
             << "Invalid input";
    else
    {
        cout << endl
             << "Fibonacci Sequence upto " << n << "th term :" << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << f1 << "\t";
            fn = f1 + f2;
            f1 = f2;
            f2 = fn;
        }
    }
    return 0;
}