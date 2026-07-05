// Lab 1.2: Write a C program to find out value of PI using Monte Carlo Simulation Technique
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    cout << "Enter number of iterations : ";
    long long itr = 0;
    if (!(cin >> itr) || itr <= 0)
        return cout << "Invalid number of iterations.", 1;

    mt19937_64 rng(static_cast<unsigned long long>(
        steady_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> dist(0.0, 1.0);

    long long count = 0;
    for (long long i = 0; i < itr; ++i)
    {
        double x = dist(rng);
        double y = dist(rng);
        double z = x * x + y * y;
        if (z <= 1.0)
            ++count;
    }

    double pi = 4.0 * static_cast<double>(count) / static_cast<double>(itr);

    cout << endl
         << "---Monte Carlo Simulation for PI---" << endl;
    cout << "Value of PI = " << pi;
    return 0;
}