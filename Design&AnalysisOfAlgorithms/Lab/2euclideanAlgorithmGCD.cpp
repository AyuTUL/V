// Lab 2: WAP to implement Euclid’s algorithm to find GCD of two numbers.
#include <iostream>
#include <stdlib.h>
using namespace std;
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int main()
{
    int a, b;
    cout << "---GCD using Euclidean Algorithm---" << endl;
    cout << "Enter 2 numbers : ";
    cin >> a >> b;
    if (a < 0 || b < 0)
    {
        cout << endl
             << "GCD of negative numbers doesn't exist.";
        exit(0);
    }
    cout << endl
         << "GCD(" << a << "," << b << ") = " << gcd(a, b);
    return 0;
}