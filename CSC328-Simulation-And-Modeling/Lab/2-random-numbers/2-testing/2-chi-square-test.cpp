// Lab 2.2.2: Write a C program that tests random numbers for frequency using chi-Square test
#include <iostream>
using namespace std;

constexpr int N = 100, kBins = 10;
constexpr float alpha = 16.9f;

int main()
{
    float XO[kBins] = {0.0f}, s = 0.0f, x[N];

    cout << "Enter " << N << " random numbers :" << endl;
    for (int i = 0; i < N; i++)
        cin >> x[i];

    for (int i = 0; i < N; i++)
    {
        int idx = static_cast<int>(x[i] * kBins);
        if (idx < 0)
            idx = 0;
        if (idx >= kBins)
            idx = kBins - 1;
        XO[idx]++;
    }

    const float expected = static_cast<float>(N) / kBins;
    for (int i = 0; i < kBins; i++)
    {
        float diff = XO[i] - expected;
        s += (diff * diff) / expected;
    }
    cout << endl
         << "---Chi-Square Test for Uniform Distribution---" << endl;
    cout << "s =  " << s << endl
         << "Alpha at  5% level of significance for n=9 is " << alpha << endl;
    if (s <= alpha)
        cout << "Random numbers are uniformly distributed";
    else
        cout << "Random numbers are not uniformly distributed";

    return 0;
}