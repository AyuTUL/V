// Lab 2.2.2: Write a C program that tests random numbers for frequency using chi-Square test
#include <iostream>
using namespace std;

#define N 100
#define alpha 16.9

void sort(float x[])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++)
            if (x[j + 1] < x[j])
            {
                float temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
            }
}

int main()
{
    float XO[10], XE[10], XOE[10], XOE2[10], R[10], s = 0.0, x[N];

    cout << "Enter " << N << " random numbers :" << endl;
    for (int i = 0; i < N; i++)
        cin >> x[i];

    sort(x);
    for (int i = 0; i < 10; i++)
    {
        XO[i] = 0.0;
        XE[i] = 10.0;
    }
    for (int i = 0; i < N; i++)
    {
        if (x[i] <= 0.1)
            XO[0]++;
        else if (x[i] <= 0.2)
            XO[1]++;
        else if (x[i] <= 0.3)
            XO[2]++;
        else if (x[i] <= 0.4)
            XO[3]++;
        else if (x[i] <= 0.5)
            XO[4]++;
        else if (x[i] <= 0.6)
            XO[5]++;
        else if (x[i] <= 0.7)
            XO[6]++;
        else if (x[i] <= 0.8)
            XO[7]++;
        else if (x[i] <= 0.9)
            XO[8]++;
        else if (x[i] <= 1.0)
            XO[9]++;
    }

    for (int i = 0; i < 10; i++)
    {
        XOE[i] = XO[i] - XE[i];
        XOE2[i] = XOE[i] * XOE[i];
        R[i] = XOE2[i] / XE[i];
        s = s + R[i];
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