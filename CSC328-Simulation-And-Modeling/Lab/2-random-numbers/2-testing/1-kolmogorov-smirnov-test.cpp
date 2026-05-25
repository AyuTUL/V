// Lab 2.2.1: Write a C program to that tests random numbers for frequency using Kolmogorov S test
#include <iostream>
using namespace std;

#define N 5
#define Dalpha 0.665

int main()
{
    float R[N], Y[N], Z[N], D1, D2, D;

    cout << "Enter " << N << " random numbers :" << endl;
    for (int i = 0; i < N; i++)
        cin >> R[i];
    cout << endl
         << "---Kolmogorov-Smirnov Test for Uniform Distribution---" << endl;
    for (int i = 0; i < N; i++)
    {
        float xi = static_cast<float>(i + 1) / N;
        Y[i] = xi - R[i];
        Z[i] = R[i] - static_cast<float>(i) / N;
    }

    D1 = Y[0];
    D2 = Z[0];
    for (int i = 1; i < N; i++)
    {
        if (D1 < Y[i])
            D1 = Y[i];
        if (D2 < Z[i])
            D2 = Z[i];
    }
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
