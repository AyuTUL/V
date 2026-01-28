// Lab 5: WAP to encrypt & decrypt user input message using One-Time Pad (OTP) cipher.
#include <bits/stdc++.h>
using namespace std;

string normalizeAZ(string s)
{
    string t = "";
    for (char ch : s)
    {
        if (isalpha((unsigned char)ch))
            t += toupper((unsigned char)ch);
    }
    return t;
}

char randomChar()
{
    static random_device rd;
    return 'A' + (rd() % 26);
}

string generateRandomKey(int length)
{
    string key;
    key.reserve(length);
    for (int i = 0; i < length; i++)
        key += randomChar();
    return key;
}

int fix(int x)
{
    x %= 26;
    if (x < 0)
        x += 26;
    return x;
}

string oneTimePad(string text, string key, bool enc)
{
    string result;
    result.reserve(text.size());

    for (int i = 0; i < (int)text.size(); i++)
    {
        int T = text[i] - 'A';
        int K = key[i] - 'A';
        int out = enc ? fix(T + K) : fix(T - K);
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

    cout << "---One-Time Pad Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2)
    {
        cout << endl
             << "Invalid choice. Please try again.";
        exit(0);
    }

    cout << endl
         << "Enter text : ";
    getline(cin, text);

    text = normalizeAZ(text);
    if (text.empty())
    {
        cout << endl
             << "Invalid text. Please try again.";
        exit(0);
    }

    if (choice == 1)
    {
        key = generateRandomKey(text.size());
        cout << "Generated key : " << key << endl
             << endl
             << "Ciphertext : " << oneTimePad(text, key, true);
    }
    else if (choice == 2)
    {
        cout << "Enter key : ";
        getline(cin, key);

        key = normalizeAZ(key);
        if (key.size() != text.size())
        {
            cout << endl
                 << "Invalid key. Please try again.";
            exit(0);
        }

        cout << endl
             << "Plaintext : " << oneTimePad(text, key, false);
    }

    return 0;
}