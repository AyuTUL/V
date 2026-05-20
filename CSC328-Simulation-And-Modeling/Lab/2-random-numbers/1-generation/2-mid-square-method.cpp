// Lab 2.1.2: Write a C program to generate 10 random numbers using mid square method
#include <iostream>
using namespace std;

int main()
{
    long int i, s, x, y, z, seed;
    int n;

    cout << "Enter seed value : ";
    if (!(cin >> seed))
        return 1;

    cout << "Enter number of random numbers to be generated : ";
    if (!(cin >> n))
        return 1;

    cout << endl
         << "---Random Number Generation using Mid Square Method---";

    for (i = 1; i <= n; i++)
    {
        s = (seed * seed);
        y = s / 10.0;
        z = y / 100.0;
        x = static_cast<long int>((y / 100.0 - z) * 100.0);
        cout << endl
             << "x =  " << x;
        seed = x;
    }

    return 0;
}