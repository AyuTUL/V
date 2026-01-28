// Lab 6: WAP to encrypt & decrypt user input message using Vernam cipher.
// wrong
#include <bits/stdc++.h>
using namespace std;

string bin8(unsigned char x)
{
    string s = "";
    for (int i = 7; i >= 0; i--)
        s += ((x >> i) & 1) ? '1' : '0';
    return s;
}

void printBorder()
{
    cout << "+--------+-----------+--------+-----------+--------+-----------+" << endl;
}

void printHeader(bool encrypt)
{
    printBorder();
    if (encrypt)
        cout << "| P_char |   P_bin   | K_char |   K_bin   | C_char |   C_bin   |" << endl;
    else
        cout << "| C_char |   C_bin   | K_char |   K_bin   | P_char |   P_bin   |" << endl;
    printBorder();
}

void printRow(char t, string tBin, char k, string kBin, char r, string rBin)
{
    cout << "|   " << t << "    | " << tBin << " |   " << k << "    | " << kBin << " |   " << r << "    | " << rBin << " |" << endl;
}

string vernamCipher(string text, string key, bool encrypt)
{
    string result = "";

    cout << endl
         << "Step-by-step XOR (8-bit):" << endl;
    printHeader(encrypt);

    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char T = (unsigned char)text[i];
        unsigned char K = (unsigned char)key[i];
        unsigned char R = T ^ K;

        printRow((char)T, bin8(T), (char)K, bin8(K), (char)R, bin8(R));

        result += (char)R;
    }

    printBorder();
    return result;
}

int main()
{
    string key, text;
    int choice;

    cout << "---Vernam Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2)
    {
        cout << endl
             << "Invalid choice. Please try again.";
        exit(0);
    }

    if (choice == 1)
    {
        cout << endl
             << "Enter text : ";
        getline(cin, text);

        if (text.empty())
        {
            cout << endl
                 << "Invalid text. Please try again.";
            exit(0);
        }

        cout << "Enter key (length must be " << text.size() << ") : ";
        getline(cin, key);

        if (key.size() != text.size())
        {
            cout << endl
                 << "Invalid key. Please try again.";
            exit(0);
        }

        cout << endl
             << "Ciphertext : " << vernamCipher(text, key, true);
    }
    else if (choice == 2)
    {
        cout << endl
             << "Enter ciphertext : ";
        getline(cin, text);

        if (text.empty())
        {
            cout << endl
                 << "Invalid ciphertext. Please try again.";
            exit(0);
        }

        cout << "Enter key (length must be " << text.size() << ") : ";
        getline(cin, key);

        if (key.size() != text.size())
        {
            cout << endl
                 << "Invalid key. Please try again.";
            exit(0);
        }

        cout << endl
             << "Plaintext : " << vernamCipher(text, key, false);
    }

    return 0;
}
