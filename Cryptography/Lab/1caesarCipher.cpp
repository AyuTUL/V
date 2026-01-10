#include <bits/stdc++.h>
using namespace std;
string normalizeAZ(const string &s)
{
    string t;
    for (char ch : s)
        if (isalpha((unsigned char)ch))
            t.push_back(toupper(ch));
    return t;
}
char shift(char ch, int k)
{
    int x = ch - 'A';
    x = (x + k) % 26;
    return char('A' + x);
}
string encryptionCaesar(string p, int k)
{
    p = normalizeAZ(p);
    k %= 26;
    string c;
    for (char ch : p)
        c.push_back(shift(ch, k));
    return c;
}
string decryptionCaesar(string c, int k)
{
    c = normalizeAZ(c);
    k %= 26;
    string p;
    for (char ch : c)
        p.push_back(tolower(shift(ch, (26 - k) % 26)));
    return p;
}
int main()
{
    string plain;
    int key;
    cout << "Enter plain text : ";
    getline(cin, plain);
    cout << "Enter key (0-25) : ";
    cin >> key;
    if (key < 0 || key > 25)
    {
        cout << endl
             << "Invalid key. Please try again.";
        exit(0);
    }
    string cipher = encryptionCaesar(plain, key);
    string decrypted = decryptionCaesar(cipher, key);
    cout << endl
         << "---Caesar Cipher---" << endl
         << "Encrypted Cipher Text = " << cipher << endl
         << "Decrypted Plain Text = " << decrypted;
    return 0;
}