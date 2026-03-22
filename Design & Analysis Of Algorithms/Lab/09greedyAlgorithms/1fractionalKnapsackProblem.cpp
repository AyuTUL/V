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

void printSortedItems(const vector<Item> &items)
{
    cout << endl
         << "---Fractional Knapsack Problem---" << endl
         << endl
         << "Items Sorted by Value per Unit Weight :" << endl;
    border(false);
    cout << "| Item | Value      | Weight     | V/W      |" << endl;
    border(false);
    for (const auto &item : items)
        printRow(item);
}

vector<Selection> selectItems(const vector<Item> &items, double capacity, double &totalValue)
{
    vector<Selection> selected;
    double remainingCapacity = capacity;
    totalValue = 0;
    for (const auto &item : items)
    {
        if (remainingCapacity <= 0)
            break;
        double fractionTaken = (item.weight <= remainingCapacity) ? 1.0 : remainingCapacity / item.weight;
        double valueGained = item.value * fractionTaken;
        remainingCapacity = (fractionTaken == 1.0) ? remainingCapacity - item.weight : 0;
        totalValue += valueGained;
        selected.push_back({item.id, item.value, item.weight, item.ratio, fractionTaken, valueGained, remainingCapacity});
    }
    return selected;
}

void printSelectedItems(const vector<Selection> &selected)
{
    cout << endl
         << "Selected Items :" << endl;
    border(true);
    cout << "| Item | Value      | Weight     | V/W      | Fraction Taken | Value Gained | Remaining Cap. |" << endl;
    border(true);
    for (const auto &entry : selected)
        printRow(entry);
}

int main()
{
    int n;
    double capacity;
    cout << "Enter number of items : ";
    cin >> n;
    vector<Item> items(n);
    cout << "Enter value and weight of each item :" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Item " << i + 1 << " : ";
        cin >> items[i].value >> items[i].weight;
        if (items[i].weight <= 0)
            return cout << "Weight must be greater than 0 for every item." << endl, 0;
        items[i] = {i + 1, items[i].value, items[i].weight, items[i].value / items[i].weight};
    }
    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.ratio > b.ratio; });
    printSortedItems(items);
    double totalValue;
    vector<Selection> selected = selectItems(items, capacity, totalValue);
    printSelectedItems(selected);
    cout << endl
         << "Maximum Value = " << fixed << setprecision(2) << totalValue;
    return 0;
}