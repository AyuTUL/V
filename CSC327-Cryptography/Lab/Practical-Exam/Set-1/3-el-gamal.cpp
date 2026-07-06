// Q 1.3: Implement the ElGamal cryptographic system for key generation, encryption, and decryption using small sample values p = 101, g = 2, private key x = 13, and message m = 45. Show the generated public key, ciphertext pair, and recovered plaintext.
#include <bits/stdc++.h>
using namespace std;

long long powerMod(long long a, long long b, long long mod)
{
    long long r = 1;
    for (a %= mod; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            r = r * a % mod;
    return r;
}

int main()
{
    long long p = 101, g = 2, x = 13, k = 7, m = 45;

    long long y = powerMod(g, x, p);

    long long c1 = powerMod(g, k, p);
    long long c2 = (m * powerMod(y, k, p)) % p;

    long long decrypted = c2 * powerMod(powerMod(c1, x, p), p - 2, p) % p;

    cout << "Public key (p,g,y) = (" << p << "," << g << "," << y << ")" << endl
         << "Ciphertext Pair = (" << c1 << "," << c2 << ")" << endl
         << "Recovered Plaintext = " << decrypted;

    return 0;
}