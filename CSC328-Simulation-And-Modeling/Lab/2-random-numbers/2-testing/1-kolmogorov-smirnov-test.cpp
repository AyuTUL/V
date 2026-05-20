// Lab 2.2.1: Write a C program to that tests random numbers for frequency using Kolmogorov S test
#include <iostream>
using namespace std;

#define N 5
#define Dalpha 0.665

int main()
{
    float R[N];
    float X[N], Y[N], Z[N];
    float D1, D2, D;

    cout << "Enter " << N << " random numbers :" << endl;
    for (int i = 0; i < N; i++)
        cin >> R[i];
    cout << endl
         << "---Kolmogorov-Smirnov Test for Uniform Distribution---" << endl;
    for (int i = 1; i <= N; i++)
        X[i - 1] = static_cast<double>(i) / N;
    for (int i = 1; i <= N; i++)
        Y[i - 1] = static_cast<double>(i) / N - R[i - 1];
    for (int i = 1; i <= N; i++)
        Z[i - 1] = R[i - 1] - static_cast<double>(i - 1) / N;

    D1 = Y[0];
    for (int i = 1; i < N; i++)
        if (D1 < Y[i])
            D1 = Y[i];
    D2 = Z[0];
    for (int i = 1; i < N; i++)
        if (D2 < Z[i])
            D2 = Z[i];
    D = (D1 > D2) ? D1 : D2;

    cout << "D =  " << D;
    if (D < Dalpha)
        cout << endl
             << "Random numbers are uniformly distributed";
    else
        cout << endl
             << "Random numbers are not uniformly distributed";

    return 0;
}
