// Lab 13: Implement Euler’s totient function computation and verify Euler’s theorem for selected values.
#include <bits/stdc++.h>
using namespace std;

long long gcdValue(long long a, long long b)
{
    while (b != 0)
    {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long powerMod(long long a, long long b, long long mod)
{
    long long result = 1;
    a %= mod;

    while (b > 0)
    {
        if (b % 2 == 1)
            result = (result * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }

    return result;
}

long long phi(long long n)
{
    long long result = n;

    for (long long p = 2; p * p <= n; p++)
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }

    if (n > 1)
        result -= result / n;
    return result;
}

int main()
{
    long long a, n;
    cout << "Enter a and n : ";
    cin >> a >> n;

    long long phiValue = phi(n);
    cout << "phi(" << n << ") = " << phiValue << endl;

    if (gcdValue(a, n) == 1)
    {
        cout << "a^phi(n) mod n = " << powerMod(a, phiValue, n) << endl;

        if (powerMod(a, phiValue, n) == 1)
            cout << "Euler’s theorem verified" << endl;
        else
            cout << "Euler’s theorem not verified" << endl;
    }
    else
        cout << "gcd(a, n) != 1, so Euler’s theorem not applicable";

    return 0;
}