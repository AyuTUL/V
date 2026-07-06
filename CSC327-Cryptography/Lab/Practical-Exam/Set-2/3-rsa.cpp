// Q 2.3: Implement the RSA algorithm for key generation, encryption, and decryption using small sample values p = 11, q = 17, and e = 7. Encrypt and decrypt a short lowercase message using the mapping a = 0, b = 1, ..., z = 25.
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

long long modInverse(long long a, long long mod)
{
    long long x, y;
    return extendedGCD(a, mod, x, y) == 1 ? (x % mod + mod) % mod : -1;
}

int main()
{
    long long p = 11, q = 17, e = 7;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long d = modInverse(e, phi);
    string message;

    cout << "RSA Key Generation :" << endl
         << "p = " << p << endl
         << "q = " << q << endl
         << "n = " << n << endl
         << "phi = " << phi << endl
         << "Public key = (" << e << ", " << n << ")" << endl
         << "Private key = (" << d << ", " << n << ")" << endl;

    cout << endl
         << "Enter message in lowercase : ";
    getline(cin, message);

    vector<long long> cipher;
    cout << endl
         << "Encrypted Ciphertext : ";
    for (char ch : message)
        if (ch == ' ')
            cout << "/ ", cipher.push_back(-1);
        else if (isalpha((unsigned char)ch))
        {
            long long c = powerMod(tolower((unsigned char)ch) - 'a', e, n);
            cipher.push_back(c);
            cout << c << ' ';
        }

    cout << endl
         << "Decrypted Plaintext : ";
    for (long long c : cipher)
        if (c == -1)
            cout << ' ';
        else
            cout << char(powerMod(c, d, n) + 'a');

    return 0;
}
