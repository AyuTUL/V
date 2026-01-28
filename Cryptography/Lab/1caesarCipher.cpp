// Lab 1: WAP to encrypt & decrypt user input message using Caesar cipher.
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
string caesar(string text, int key, bool enc)
{
    text = normalizeAZ(text);
    key %= 26;
    string out;
    if (enc)
        for (char ch : text)
            out.push_back(shift(ch, key));
    else
        for (char ch : text)
            out.push_back(tolower(shift(ch, (26 - key) % 26)));
    return out;
}

int main()
{
    string text;
    int choice, key;

    cout << "---Caesar Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cout << endl
             << "Invalid choice. Please try again.";
        exit(0);
    }

    cout << endl
         << "Enter key (0-25) : ";
    cin >> key;
    cin.ignore();

    if (key < 0 || key > 25)
    {
        cout << endl
             << "Invalid key. Please try again.";
        exit(0);
    }

    cout << "Enter text : ";
    getline(cin, text);

    if (choice == 1)
        cout << endl
             << "Ciphertext : " << caesar(text, key, true);
    else if (choice == 2)
        cout << endl
             << "Plaintext : " << caesar(text, key, false);

    return 0;
}