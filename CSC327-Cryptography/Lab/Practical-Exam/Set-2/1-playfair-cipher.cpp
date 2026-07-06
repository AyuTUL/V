// Q 2.1: Implement the Playfair cipher encryption and decryption program using a keyword-based 5×5 matrix. Use keyword “MONARCHY” and plaintext “INSTRUMENTS”, and show the prepared digraphs before encryption.
#include <bits/stdc++.h>
using namespace std;

string normalizeAZ(string s)
{
    string t;
    for (char ch : s)
        if (isalpha((unsigned char)ch))
            t += (ch = toupper(ch)) == 'J' ? 'I' : ch;
    return t;
}

void buildMatrix(string key, char m[5][5])
{
    bool used[26] = {0};
    used['J' - 'A'] = 1;
    key = normalizeAZ(key);

    string k;
    for (char ch : key)
        if (!used[ch - 'A'])
        {
            used[ch - 'A'] = 1;
            k += ch;
        }

    for (char ch = 'A'; ch <= 'Z'; ch++)
        if (!used[ch - 'A'])
        {
            used[ch - 'A'] = 1;
            k += ch;
        }

    for (int p = 0; p < 25; p++)
        m[p / 5][p % 5] = k[p];
}

void displayMatrix(char m[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}

void findPosition(char m[5][5], char ch, int &r, int &c)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == ch)
            {
                r = i;
                c = j;
                return;
            }
}

string makePairs(string p)
{
    p = normalizeAZ(p);
    string d;
    for (int i = 0; i < (int)p.size();)
    {
        char a = p[i];
        char b = (i + 1 < (int)p.size()) ? p[i + 1] : 'X';
        if (a == b)
        {
            d += a;
            d += 'X';
            i++;
        }
        else
        {
            d += a;
            d += b;
            i += 2;
        }
    }
    if (d.size() % 2 == 1)
        d += 'X';
    return d;
}

string playfair(string text, string key, bool enc)
{
    char m[5][5];
    buildMatrix(key, m);

    if (enc)
        text = makePairs(text);
    else
        text = normalizeAZ(text);

    string out;
    int shift = enc ? 1 : 4;
    for (int i = 0; i < (int)text.size(); i += 2)
    {
        char a = text[i], b = text[i + 1];
        int r1, c1, r2, c2;
        findPosition(m, a, r1, c1);
        findPosition(m, b, r2, c2);

        if (r1 == r2)
        {
            out += m[r1][(c1 + shift) % 5];
            out += m[r2][(c2 + shift) % 5];
        }
        else if (c1 == c2)
        {
            out += m[(r1 + shift) % 5][c1];
            out += m[(r2 + shift) % 5][c2];
        }
        else
        {
            out += m[r1][c2];
            out += m[r2][c1];
        }
    }
    if (!enc)
        transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

int main()
{
    string key = "MONARCHY", text = "INSTRUMENTS";
    char keyMatrix[5][5];
    buildMatrix(key, keyMatrix);

    cout << endl
         << "Key matrix :" << endl;
    displayMatrix(keyMatrix);

    string prepared = makePairs(text);
    string ciphertext = playfair(text, key, true);
    string decrypted = playfair(ciphertext, key, false);

    cout << endl
         << "Digraphs : ";
    for (int i = 0; i < (int)prepared.size(); i += 2)
    {
        cout << prepared[i] << prepared[i + 1];
        if (i + 2 < (int)prepared.size())
            cout << " ";
    }

    cout << endl
         << "Ciphertext : " << ciphertext << endl
         << "Plaintext : " << decrypted;

    return 0;
}