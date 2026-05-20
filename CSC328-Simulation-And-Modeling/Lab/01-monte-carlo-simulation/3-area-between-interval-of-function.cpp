// Lab 1.3: Write a C program to find area between given interval of a function using Monte Carlo Simulation method
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    constexpr int xl = 1, yl = 1, xu = 2, yu = 4, N = 10000;
    int n = 0;

    mt19937_64 rng(static_cast<unsigned long long>(
        steady_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> distX(xl, xu);
    uniform_real_distribution<double> distY(yl, yu);

    for (int i = 0; i < N; ++i)
    {
        double xran = distX(rng);
        double yran = distY(rng);
        if (xran * xran <= yran)
            ++n;
    }

    cout << endl
         << "---Monte Carlo Simulation for Area Calculation---" << endl;

    double area = yu * (xu - xl) * static_cast<double>(n) / N;
    cout << "Number of points = " << n << endl
         << "Area = " << area;
    return 0;
}