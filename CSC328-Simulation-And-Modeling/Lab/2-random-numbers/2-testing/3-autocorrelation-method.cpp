// Lab 2.2.3: Write a program to test random numbers for independence using autocorrelation method
#define N 30
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int i, m, M, k;
    i = 2, m = 5;
    M = ((N - i) / m) - 1;

    float s35 = 0, r35, z0, R[N];

    cout << "Enter " << N << " random numbers :" << endl;
    for (int idx = 0; idx < N; idx++)
        cin >> R[idx];

    for (k = 0; k <= M; k++)
        s35 += R[i + k * m] * R[i + (k + 1) * m];
    s35 = (s35 / (M + 1)) - 0.25;
    r35 = sqrt(13 * M + 7) / (12 * (M + 1));
    cout << endl
         << "---Autocorrelation Test for Independence---" << endl;
    z0 = r35 / s35;
    if (z0 <= 1.96)
        cout << "The numbers are independent";
    else
        cout << "The numbers are not independent";

    return 0;
}