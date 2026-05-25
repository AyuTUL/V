// Lab 4:  Write a program to simulate the game called DiceToss.
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Roll()
{
    return 1 + rand() % 5;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int sa = Roll() + Roll();
    int sb = Roll() + Roll();
    cout << "---Dice Toss Game---" << endl;
    if (sa > sb)
        cout << "A wins the game by " << sa << " points";
    else
        cout << "B wins the game by " << sb << " points";
    return 0;
}