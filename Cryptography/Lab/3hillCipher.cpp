// Lab 3: WAP to encrypt & decrypt user input message using Hill cipher.
#include <bits/stdc++.h>
using namespace std;

#define MAX 10
int N;

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

bool inverseMatrixGauss(int key[MAX][MAX], int inv[MAX][MAX])
{
    int aug[MAX][2 * MAX];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < 2 * N; j++)
            aug[i][j] = (j < N) ? fix(key[i][j]) : (j - N == i);

    for (int col = 0; col < N; col++)
    {
        int pivot = -1;

        for (int row = col; row < N; row++)
            if (gcd(aug[row][col], 26) == 1)
            {
                pivot = row;
                break;
            }

        if (pivot == -1)
            return false;

        if (pivot != col)
            for (int j = 0; j < 2 * N; j++)
                swap(aug[pivot][j], aug[col][j]);

        int invPivot = invMod26(aug[col][col]);
        for (int j = 0; j < 2 * N; j++)
            aug[col][j] = fix(aug[col][j] * invPivot);

        for (int r = 0; r < N; r++)
        {
            if (r == col)
                continue;
            int factor = aug[r][col];
            for (int j = 0; j < 2 * N; j++)
                aug[r][j] = fix(aug[r][j] - factor * aug[col][j]);
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = aug[i][j + N];

    return true;
}

bool isKeyValid(int key[MAX][MAX])
{
    int inv[MAX][MAX];
    return inverseMatrixGauss(key, inv);
}

string hillCipher(string text, int key[MAX][MAX], bool encrypt)
{
    text = normalizeAZ(text);

    while (text.size() % N != 0)
        text += 'X';

    int invKey[MAX][MAX];
    if (!encrypt)
        inverseMatrixGauss(key, invKey);

    string result;

    for (int i = 0; i < text.size(); i += N)
    {
        for (int r = 0; r < N; r++)
        {
            int sum = 0;
            for (int c = 0; c < N; c++)
            {
                int val = text[i + c] - 'A';
                sum += (encrypt ? key[r][c] : invKey[r][c]) * val;
            }
            result += char('A' + fix(sum));
        }
    }
    if (!encrypt)
        transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main()
{
    string text;
    int key[MAX][MAX], choice;

    cout << "---Hill Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2)
    {
        cout << endl
             << "Invalid choice. Please try again.";
        exit(0);
    }

    cout << endl
         << "Enter order of matrix : ";
    cin >> N;

    cout << "Enter key matrix :" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> key[i][j];

    if (choice == 2 && !isKeyValid(key))
    {
        cout << endl
             << "Invalid key. Please try again.";
        exit(0);
    }

    cin.ignore();

    cout << endl
         << "Enter text : ";
    getline(cin, text);

    if (choice == 1)
        cout << endl
             << "Ciphertext : " << hillCipher(text, key, true);
    else if (choice == 2)
        cout << endl
             << "Plaintext : " << hillCipher(text, key, false);

    return 0;
}