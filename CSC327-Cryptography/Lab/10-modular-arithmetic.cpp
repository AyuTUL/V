// Lab 10: Implement modular arithmetic operations and compute additive inverses in Zn for given inputs.
#include <bits/stdc++.h>
using namespace std;

long long normalize(long long x, long long n)
{
    x %= n;
    if (x < 0)
        x += n;
    return x;
}

int main()
{
    long long a, b, n;
    cout << "Enter a, b and n : ";
    cin >> a >> b >> n;

    if (n <= 0)
        return cout << "n must be positive", 0;

    long long A = normalize(a, n);
    long long B = normalize(b, n);

    cout << endl
         << "---Modular Arithmetic & Additive Inverses in Z" << n << "---" << endl;

    cout << "(" << a << " + " << b << ") mod " << n << " = " << normalize(A + B, n) << endl
         << "(" << a << " - " << b << ") mod " << n << " = " << normalize(A - B, n) << endl
         << "(" << a << " * " << b << ") mod " << n << " = " << normalize(A * B, n) << endl
         << "Additive inverse of " << a << " = " << normalize(-A, n) << endl
         << "Additive inverse of " << b << " = " << normalize(-B, n) << endl;

    return 0;
}