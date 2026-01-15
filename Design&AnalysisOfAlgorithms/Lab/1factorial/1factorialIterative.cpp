// Lab 1.1: WAP to compute factorial of a number using iterative method.
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
    int n, fact = 1;
    cout << "---Factorial using Iterative Method---" << endl;
    cout << "Enter number : ";
    cin >> n;
    if (n < 0)
    {
        cout << endl
             << "Factorial of negative number doesn't exist.";
        exit(0);
    }
    for (int i = n; i >= 1; i--)
        fact *= i;
    cout << endl
         << n << "! = " << fact;
    return 0;
}