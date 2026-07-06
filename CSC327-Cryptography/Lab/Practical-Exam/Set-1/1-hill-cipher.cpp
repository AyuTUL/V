// Q 1.1: Implement the Hill cipher encryption and decryption program using the 2×2 key matrix [[3, 3], [2, 5]] under modulo 26. Encrypt plaintext “HELP” and verify the result through decryption.
#include <bits/stdc++.h>
using namespace std;

string normalizeAZ(string s)
{
    string t;
    for (char c : s)
        if (isalpha(c))
            t += toupper(c);
    return t;
}

int fix(int x)
{
    x %= 26;
    if (x < 0)
        x += 26;
    return x;
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int invMod26(int a)
{
    a = fix(a);
    for (int i = 1; i < 26; i++)
        if (fix(a * i) == 1)
            return i;
    return -1;
}

bool inverseMatrixGauss(int key[2][2], int inv[2][2])
{
    int aug[2][4];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            aug[i][j] = (j < 2) ? fix(key[i][j]) : (j - 2 == i);

    for (int col = 0; col < 2; col++)
    {
        int pivot = -1;

        for (int row = col; row < 2; row++)
            if (gcd(aug[row][col], 26) == 1)
            {
                pivot = row;
                break;
            }

        if (pivot == -1)
            return false;

        if (pivot != col)
            for (int j = 0; j < 4; j++)
                swap(aug[pivot][j], aug[col][j]);

        int invPivot = invMod26(aug[col][col]);
        for (int j = 0; j < 4; j++)
            aug[col][j] = fix(aug[col][j] * invPivot);

        for (int r = 0; r < 2; r++)
        {
            if (r == col)
                continue;
            int factor = aug[r][col];
            for (int j = 0; j < 4; j++)
                aug[r][j] = fix(aug[r][j] - factor * aug[col][j]);
        }
    }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv[i][j] = aug[i][j + 2];

    return true;
}

string hillCipher(string text, int key[2][2], bool enc)
{
    text = normalizeAZ(text);

    while (text.size() % 2 != 0)
        text += 'X';

    int invKey[2][2];
    if (!enc)
        inverseMatrixGauss(key, invKey);

    string result;

    for (int i = 0; i < text.size(); i += 2)
        for (int r = 0; r < 2; r++)
        {
            int sum = 0;
            for (int c = 0; c < 2; c++)
            {
                int val = text[i + c] - 'A';
                sum += (enc ? key[r][c] : invKey[r][c]) * val;
            }
            result += char('A' + fix(sum));
        }
    if (!enc)
        transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main()
{
    string text = "HELP";
    int key[2][2] = {{3, 3}, {2, 5}};
    string cipher = hillCipher(text, key, true);
    string plain = hillCipher(cipher, key, false);

    cout << "Ciphertext : " << cipher << endl
         << "Plaintext : " << plain;

    return 0;
}