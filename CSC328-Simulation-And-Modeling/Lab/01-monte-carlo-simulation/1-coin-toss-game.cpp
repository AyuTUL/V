// Lab 1.2: Write a program to simulate coin toss game using Monte Carlo Simulation Technique
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    cout << "Enter number of iterations : ";
    long long itr;
    if (!(cin >> itr) || itr <= 0)
        return cout << "Invalid number of iterations.", 1;

    mt19937_64 rng(static_cast<unsigned long long>(
        steady_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> dist(0.0, 1.0);

    long long head = 0, tail = 0;
    for (long long i = 0; i < itr; ++i)
    {
        double r = dist(rng);
        if (r <= 0.5)
            ++head;
        else
            ++tail;
    }

    cout << endl
         << "---Monte Carlo Simulation for Coin Toss---" << endl;
    cout << "Head = " << head << endl
         << "Tail = " << tail << endl;

    if (head > tail)
        cout << "Head wins by " << (head - tail);
    else if (tail > head)
        cout << "Tail wins by " << (tail - head);
    else
        cout << "It's a tie.";

    return 0;
}
