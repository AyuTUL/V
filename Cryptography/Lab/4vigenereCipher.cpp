// Lab 4: WAP to encrypt & decrypt user input message using Vigenere cipher.
#include <bits/stdc++.h>
using namespace std;

string normalizeAZ(string s)
{
    string t = "";
    for (char ch : s)
    {
        if (isalpha((unsigned char)ch))
            t += (char)toupper((unsigned char)ch);
    }
    return t;
}

int fix(int x)
{
    x %= 26;
    if (x < 0)
        x += 26;
    return x;
}

string vigenere(string text, string key, bool enc)
{
    text = normalizeAZ(text);
    key = normalizeAZ(key);

    string result = "";
    for (int i = 0; i < (int)text.size(); i++)
    {
        int P = text[i] - 'A';
        int K = key[i % key.size()] - 'A';
        int out = enc ? fix(P + K) : fix(P - K);
        result += (char)('A' + out);
    }

    if (!enc)
        transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main()
{
    string key, text;
    int choice;

    cout << "---Vigenere Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2)
    {
        cout << endl
             << "Invalid choice. Please try again.";
        exit(0);
    }

    cout << endl
         << "Enter key : ";
    getline(cin, key);

    for (char ch : key)
        if (!isalpha((unsigned char)ch))
        {
            cout << endl
                 << "Invalid key. Please try again.";
            exit(0);
        }

    cout << "Enter text : ";
    getline(cin, text);

    if (choice == 1)
        cout << endl
             << "Ciphertext : " << vigenere(text, key, true);
    else if (choice == 2)
        cout << endl
             << "Plaintext : " << vigenere(text, key, false);

    return 0;
}