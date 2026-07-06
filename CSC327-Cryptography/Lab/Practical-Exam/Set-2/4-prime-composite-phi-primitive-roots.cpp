// Q 2.4: Test whether n = 91 is prime/composite, compute phi(45), and check primitive roots modulo 17.
#include <bits/stdc++.h>
using namespace std;

long long powerMod(long long a, long long b, long long mod)
{
    long long r = 1;
    for (a %= mod; b; b >>= 1, a = (a * a) % mod)
        if (b & 1)
            r = (r * a) % mod;
    return r;
}

bool primality(long long n)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    long long d = n - 1;
    int s = 0;

    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    int bases[] = {2, 3, 5, 7, 11};
    for (int i = 0; i < 5; i++)
    {
        long long a = bases[i];

        if (a >= n)
            continue;

        long long x = powerMod(a, d, n);
        if (x == 1 || x == n - 1)
            continue;

        bool witness = true;
        for (int r = 1; r < s; r++)
        {
            x = (x * x) % n;
            if (x == n - 1)
            {
                witness = false;
                break;
            }
        }

        if (witness)
            return false;
    }

    return true;
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

vector<long long> primeFactors(long long n)
{
    vector<long long> factors;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }

    if (n > 1)
        factors.push_back(n);
    return factors;
}

bool isPrimitiveRoot(long long g, long long p, const vector<long long> &factors)
{
    long long phi = p - 1;

    for (long long f : factors)
        if (powerMod(g, phi / f, p) == 1)
            return false;

    return true;
}
int main()
{
    long long n1 = 91, n2 = 45, p = 17;
    if (primality(n1))
        cout << n1 << " is Probably Prime" << endl;
    else
        cout << n1 << " is Composite" << endl;
    long long phiValue = phi(n2);
    cout << "phi(" << n2 << ") = " << phiValue << endl;
    vector<long long> factors = primeFactors(p - 1);
    long long g = 3;

    if (isPrimitiveRoot(g, p, factors))
        cout << g << " is a primitive root modulo " << p << endl;
    else
        cout << g << " is not a primitive root modulo " << p << endl;

    cout << "Primitive roots of modulo " << p << " : ";
    for (long long i = 2; i < p; i++)
        if (isPrimitiveRoot(i, p, factors))
            cout << i << " ";
    return 0;
}