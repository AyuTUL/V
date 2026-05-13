// Lab 15: Implement the Diffie–Hellman key exchange and demonstrate how both parties derive the same shared secret key.
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

int main()
{
    long long p, g, a, b;
    cout << "Enter prime p and primitive root g : ";
    cin >> p >> g;

    cout << "Enter private key of Alice : ";
    cin >> a;
    cout << "Enter private key of Bob : ";
    cin >> b;

    long long A = powerMod(g, a, p);
    long long B = powerMod(g, b, p);

    long long sharedAlice = powerMod(B, a, p);
    long long sharedBob = powerMod(A, b, p);

    cout << "Alice public value = " << A << endl;
    cout << "Bob public value = " << B << endl;
    cout << "Shared key (Alice) = " << sharedAlice << endl;
    cout << "Shared key (Bob) = " << sharedBob << endl;

    return 0;
}