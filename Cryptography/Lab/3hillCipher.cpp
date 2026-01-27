// check output plaintext small cipher capital
#include <bits/stdc++.h>
using namespace std;

#define MAX 10 // max matrix size
int N;

/* ---------- Utility ---------- */

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

string normalizeAZ(string s)
{
    string t;
    for (char c : s)
        if (isalpha(c))
            t += toupper(c);
    return t;
}

/* ---------- Matrix Operations ---------- */

void getCofactor(int mat[MAX][MAX], int temp[MAX][MAX],
                 int p, int q, int n)
{
    int i = 0, j = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (r != p && c != q)
            {
                temp[i][j++] = mat[r][c];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
}

int determinant(int mat[MAX][MAX], int n)
{
    if (n == 1)
        return mat[0][0];

    int temp[MAX][MAX];
    int det = 0, sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

bool inverseMatrix(int key[MAX][MAX], int inv[MAX][MAX])
{
    int det = fix(determinant(key, N));
    if (gcd(det, 26) != 1)
        return false;

    int detInv = invMod26(det);
    int adj[MAX][MAX];
    int temp[MAX][MAX];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(key, temp, i, j, N);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant(temp, N - 1); // transpose
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = fix(adj[i][j] * detInv);

    return true;
}

/* ---------- Hill Cipher ---------- */

string hillCipher(string text,
                  int key[MAX][MAX],
                  bool encrypt)
{
    text = normalizeAZ(text);
    while (text.size() % N != 0)
        text += 'X';

    int invKey[MAX][MAX];
    if (!encrypt && !inverseMatrix(key, invKey))
        return "INVALID KEY";

    string result;

    for (int i = 0; i < text.size(); i += N)
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
    return result;
}

/* ---------- Main ---------- */

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
         << "Enter order N : ";
    cin >> N;

    cout << "Enter key matrix :" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> key[i][j];

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
