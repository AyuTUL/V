// Lab 7: Implement the Rail Fence transposition cipher encryption and decryption program for a given key (rails).
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

void printRailFence(const vector<vector<char>> &rail)
{
    int r = rail.size(), c = rail[0].size();
    cout << endl;
    for (int j = 0; j < c; j++)
        cout << "+---";
    cout << "+" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << "| " << rail[i][j] << " ";
        cout << "|" << endl;
        for (int j = 0; j < c; j++)
            cout << "+---";
        cout << "+" << endl;
    }
}

string railFence(string text, int rails, bool enc)
{
    int n = text.size(), row = 0, dir = 1;
    vector<vector<char>> rail(rails, vector<char>(n, ' '));

    for (int i = 0; i < n; i++)
    {
        rail[row][i] = enc ? text[i] : '*';
        dir = (row == 0) ? 1 : (row == rails - 1 ? -1 : dir);
        row += dir;
    }

    if (!enc)
        for (int i = 0, k = 0; i < rails; i++)
            for (int j = 0; j < n; j++)
                if (rail[i][j] == '*')
                    rail[i][j] = text[k++];

    printRailFence(rail);

    string res;
    if (enc)
    {
        for (int i = 0; i < rails; i++)
            for (int j = 0; j < n; j++)
                if (rail[i][j] != ' ')
                    res += rail[i][j];
    }
    else
    {
        row = 0, dir = 1;
        for (int i = 0; i < n; i++)
        {
            res += rail[row][i];
            dir = (row == 0) ? 1 : (row == rails - 1 ? -1 : dir);
            row += dir;
        }
    }

    return res;
}

int main()
{
    int choice, rails;
    string text;

    cout << "---Rail Fence Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice < 1 || choice > 2)
        return cout << endl
                    << "Invalid choice." << endl,
               0;

    cout << endl
         << "Enter text : ";
    getline(cin, text);

    text = normalizeAZ(text);

    if (text.empty())
        return cout << endl
                    << "Invalid text." << endl,
               0;

    cout << "Enter number of rails : ";
    cin >> rails;

    if (rails < 1 || rails >= (int)text.size())
        return cout << endl
                    << "Invalid number of rails." << endl,
               0;

    if (rails == 1)
        return cout << endl
                    << "Result : " << text,
               0;

    string res = railFence(text, rails, choice == 1);

    if (choice == 2)
        for (char &c : res)
            c = tolower((unsigned char)c);

    cout << endl
         << (choice == 1 ? "Ciphertext : " : "Plaintext : ") << res;
}
