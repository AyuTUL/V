// Lab 4:  Write a program to simulate the game called DiceToss.
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Arand()
{
    int r;
    r = 1 + rand() % 5;
    return r;
}

int Brand()
{
    int r;
    r = 1 + rand() % 5;
    return r;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int sa = 0, sb, a, b, x, y;
    a = Arand();
    b = Arand();
    sa = a + b;
    x = Brand();
    y = Brand();
    sb = x + y;
    cout << "---Dice Toss Game---" << endl;
    if (sa > sb)
        cout << "A wins the game by " << sa << " points";
    else
        cout << "B wins the game by " << sb << " points";
    return 0;
}