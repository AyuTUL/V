// Lab 10.1: WAP to implement fractional knapsack problem.
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
    cout << (wide
                 ? "+------+------------+------------+----------+----------------+--------------+----------------+\n"
                 : "+------+------------+------------+----------+\n");
}

void printRow(const Item &it)
{
    cout << "| " << left << setw(4) << it.id
         << " | " << setw(10) << fixed << setprecision(2) << it.value
         << " | " << setw(10) << it.weight
         << " | " << setw(8) << it.ratio << " |" << endl;
    border(false);
}

void printRow(const Selection &s)
{
    cout << "| " << left << setw(4) << s.id
         << " | " << setw(10) << fixed << setprecision(2) << s.value
         << " | " << setw(10) << s.weight
         << " | " << setw(8) << s.ratio
         << " | " << setw(14) << s.fraction
         << " | " << setw(12) << s.gained
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
    {
        cout << "Number of items must be greater than 0." << endl;
        return 0;
    }

    vector<Item> items(n);
    cout << "Enter value and weight of each item :" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Item " << i + 1 << " : ";
        cin >> items[i].value >> items[i].weight;
        if (items[i].weight <= 0)
        {
            cout << "Weight must be greater than 0 for every item." << endl;
            return 0;
        }
        items[i].id = i + 1;
        items[i].ratio = items[i].value / items[i].weight;
    }

    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    if (capacity < 0)
    {
        cout << "Knapsack capacity cannot be negative." << endl;
        return 0;
    }

    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.ratio > b.ratio; });

    double totalValue = 0, rem = capacity;
    vector<Selection> selected;

    cout << endl
         << "---Fractional Knapsack Problem---" << endl
         << endl;
    border(false);
    cout << "| Item | Value      | Weight     | V/W      |" << endl;
    border(false);
    for (int i = 0; i < n; i++)
        printRow(items[i]);

    for (int i = 0; i < n; i++)
    {
        const Item &it = items[i];

        if (rem <= 0)
            break;

        double frac;
        double gained;

        if (it.weight <= rem)
        {
            frac = 1.0;
            gained = it.value;
            rem -= it.weight;
        }
        else
        {
            frac = rem / it.weight;
            gained = it.value * frac;
            rem = 0;
        }

        totalValue += gained;
        selected.push_back({it.id, it.value, it.weight, it.ratio, frac, gained, rem});
    }

    cout << endl
         << "Selected Items :" << endl;
    border(true);
    cout << "| Item | Value      | Weight     | V/W      | Fraction Taken | Value Gained | Remaining Cap. |" << endl;
    border(true);
    for (int i = 0; i < (int)selected.size(); i++)
        printRow(selected[i]);

    cout << endl
         << "Maximum Value = " << fixed << setprecision(2) << totalValue << endl;

    return 0;
}