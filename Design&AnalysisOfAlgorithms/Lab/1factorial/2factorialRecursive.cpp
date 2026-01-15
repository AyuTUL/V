// Lab 1.2: WAP to compute factorial of a number using iterative method.
#include <iostream>
#include <stdlib.h>
using namespace std;
int fact(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * fact(n - 1);
}
int main()
{
    int n;
    cout << "---Fibonacci Sequence using Recursive Method---" << endl;
    cout << "Enter number : ";
    cin >> n;
    if (n < 0)
    {
        cout << endl
             << "Factorial of negative number doesn't exist.";
        exit(0);
    }
    cout << endl
         << n << "! = " << fact(n);
    return 0;
}