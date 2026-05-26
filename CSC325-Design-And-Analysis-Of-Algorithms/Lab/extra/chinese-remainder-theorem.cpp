// Lab 13: Implementation of Chinese Remainder Theorem (CRT)
#include <iostream>
#include <stdlib.h>
using namespace std;
int gcd(int a, int b)
{
    if (b == 0)
        return (a);
    return (gcd(b, a % b));
}
int modInverse(int M, int mod)
{
    int i = 1;
    while ((M * i) % mod != 1)
        i++;
    return (i);
}
int CRT(int n, int a[], int m[])
{
    int M = 1;
    for (int i = 0; i < n; i++)
        M *= m[i];
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        int Mi = M / m[i];
        int MiInverse = modInverse(Mi, m[i]);
        result += a[i] * Mi * MiInverse;
    }
    return (result % M);
}
void show(int n, int a[], int m[])
{
    for (int i = 0; i < n; i++)
        cout << "x = " << a[i] << " ( MOD " << m[i] << " ) " << endl;
}
void check(int n, int m[])
{
    bool coPrime = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (gcd(m[i], m[j]) != 1)
            {
                cout << "Error : Moduli " << m[i] << " & " << m[j] << " are not co-prime";
                coPrime = false;
                exit(1);
            }
        if (!coPrime)
            break;
    }
}
int main()
{
    int n, *a, *m;
    cout << "Enter no. of congruencies : ";
    cin >> n;
    a = new int[n];
    m = new int[n];
    cout << "Enter " << n << " remainders : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Enter " << n << " moduli : ";
    for (int i = 0; i < n; i++)
        cin >> m[i];
    show(n, a, m);
    check(n, m);
    cout << endl
         << "---Chinese Remainder Theorem---" << endl;
    cout << "x = " << CRT(n, a, m);
    delete[] a;
    delete[] m;
    return 0;
}