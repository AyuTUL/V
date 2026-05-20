// Lab 2.1.1: Write a C program to generate 10 random numbers using Linear Congruential method
#include <iostream>
using namespace std;

int main()
{
    int x0, x, a, c, M = 101;
    x0 = 31, a = 17, c = 13;
    double r;

    cout << endl
         << "---Random Number Generation using Linear Congruential Method---" << endl;

    for (int i = 1; i <= 15; i++)
    {
        x = (a * x0 + c) % M;
        r = static_cast<double>(x) / M;
        cout << r << "   ";
        x0 = x;
    }

    return 0;
}