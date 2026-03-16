// Lab 9.1: WAP to implement fractional knapsack problem.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Item
{
    int id;
    double value, weight, ratio;
};
struct Selection
{
    int id;
    double value, weight, ratio, fraction, gained, remaining;
};

void border(bool wide)
{
    cout << (wide ? "+------+------------+------------+----------+----------------+--------------+----------------+"
                  : "+------+------------+------------+----------+")
         << endl;
}

void printRow(const Item &it)
{
    cout << left << fixed << setprecision(2)
         << "| " << setw(4) << it.id << " | " << setw(10) << it.value
         << " | " << setw(10) << it.weight << " | " << setw(8) << it.ratio << " |" << endl;
    border(false);
}

void printRow(const Selection &s)
{
    cout << left << fixed << setprecision(2)
         << "| " << setw(4) << s.id << " | " << setw(10) << s.value
         << " | " << setw(10) << s.weight << " | " << setw(8) << s.ratio
         << " | " << setw(14) << s.fraction << " | " << setw(12) << s.gained
         << " | " << setw(14) << s.remaining << " |" << endl;
    border(true);
}

int main()
{
    int n;
    double capacity;
    cout << "Enter number of items : ";
    cin >> n;
    if (n <= 0)
        return cout << "Number of items must be greater than 0." << endl, 0;

    vector<Item> items(n);
    cout << "Enter value and weight of each item :" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Item " << i + 1 << " : ";
        cin >> items[i].value >> items[i].weight;
        if (items[i].weight <= 0)
            return cout << "Weight must be greater than 0 for every item." << endl, 0;
        items[i].id = i + 1;
        items[i].ratio = items[i].value / items[i].weight;
    }

    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    if (capacity < 0)
        return cout << "Knapsack capacity cannot be negative." << endl, 0;

    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.ratio > b.ratio; });

    double totalValue = 0, rem = capacity;
    vector<Selection> selected;

    cout << endl
         << "---Fractional Knapsack Problem---" << endl
         << endl
         << "Items Sorted by Value per Unit Weight :" << endl;
    border(false);
    cout << "| Item | Value      | Weight     | V/W      |" << endl;
    border(false);
    for (int i = 0; i < n; i++)
        printRow(items[i]);

    for (int i = 0; i < n; i++)
    {
        if (rem <= 0)
            break;
        double frac = (items[i].weight <= rem) ? 1.0 : rem / items[i].weight;
        double gained = items[i].value * frac;
        rem = (frac == 1.0) ? rem - items[i].weight : 0;
        totalValue += gained;
        selected.push_back({items[i].id, items[i].value, items[i].weight, items[i].ratio, frac, gained, rem});
    }

    cout << endl
         << "Selected Items :" << endl;
    border(true);
    cout << "| Item | Value      | Weight     | V/W      | Fraction Taken | Value Gained | Remaining Cap. |" << endl;
    border(true);
    for (int i = 0; i < (int)selected.size(); i++)
        printRow(selected[i]);

    cout << endl
         << "Maximum Value = " << fixed << setprecision(2) << totalValue;
    return 0;
}