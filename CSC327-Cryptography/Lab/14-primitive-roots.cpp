// Lab 14: Implement a primitive root checking program and find primitive roots for a given prime modulus.
#include <bits/stdc++.h>
using namespace std;

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

bool isPrime(long long n)
{
    if (n < 2)
        return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

vector<long long> primeFactors(long long n)
{
    vector<long long> factors;

    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        factors.push_back(n);
    return factors;
}

bool isPrimitiveRoot(long long g, long long p, vector<long long> factors)
{
    long long phi = p - 1;

    for (int i = 0; i < (int)factors.size(); i++)
    {
        if (powerMod(g, phi / factors[i], p) == 1)
            return false;
    }

    return true;
}

int main()
{
    long long p, g;
    cout << "Enter prime modulus p : ";
    cin >> p;
    cout << "Enter value g to check : ";
    cin >> g;

    if (!isPrime(p))
    {
           cout << endl
               << "p must be prime";
        return 0;
    }

    vector<long long> factors = primeFactors(p - 1);

    if (isPrimitiveRoot(g, p, factors))
        cout << g << " is a primitive root modulo " << p << endl;
    else
        cout << g << " is not a primitive root modulo " << p << endl;

    cout << "Primitive roots modulo " << p << " : ";
    for (long long i = 2; i < p; i++)
    {
        if (isPrimitiveRoot(i, p, factors))
            cout << i << " ";
    }
    cout << endl;

    return 0;
}