// Q 1.2: Implement the Extended Euclidean Algorithm to compute gcd and multiplicative inverse in Zn. Test the program for 17 mod 43 and 12 mod 26, and clearly show whether the inverse exists.
#include <bits/stdc++.h>
using namespace std;

long long extendedGCD(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main()
{
    long long a, n, x, y;
    cout << "Enter a and n : ";
    cin >> a >> n;

    if (n <= 0)
        return cout << "Invalid modulus: n must be positive", 0;

    long long gcd = extendedGCD(a, n, x, y);

    cout << endl
         << "GCD = " << gcd << endl;

    if (gcd == 1)
    {
        long long inverse = (x % n + n) % n;
        cout << "Multiplicative Inverse in Z" << n << " = " << inverse << endl;
    }
    else
        cout << "Inverse does not exist: a & n are not coprime" << endl;

    return 0;
}