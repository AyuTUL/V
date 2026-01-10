// Lab 1.1: WAP to find factorial of given number.
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
    cout << "Enter an integer : ";
    cin >> n;
    if (n < 0)
    {
        cout << "Factorial of negative integer doesn't exist." ;
        exit(0);
    }
    cout << n << "! = " << fact(n);
    return 0;
}