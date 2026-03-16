// Lab 12: 0-1 Knapsack using Greedy approach (by profit/weight ratio)
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Item
{
    int id;
    int profit;
    int weight;
    double ratio;
};

bool compareByRatio(const Item &a, const Item &b)
{
    return a.ratio > b.ratio;
}

int main()
{
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of items must be greater than 0." << endl;
        return 0;
    }

    vector<Item> items(n);
    cout << "Enter profit and weight for each item:" << endl;

    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        cout << "Item " << items[i].id << ": ";
        cin >> items[i].profit >> items[i].weight;

        if (items[i].weight <= 0)
        {
            cout << "Weight must be greater than 0." << endl;
            return 0;
        }

        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0)
    {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    sort(items.begin(), items.end(), compareByRatio);

    int totalProfit = 0;
    int totalWeight = 0;

    cout << "\nSelected items:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (totalWeight + items[i].weight <= capacity)
        {
            totalWeight += items[i].weight;
            totalProfit += items[i].profit;
            cout << "Item " << items[i].id << " (p=" << items[i].profit << ", w=" << items[i].weight << ")" << endl;
        }
    }

    cout << "Total weight = " << totalWeight << endl;
    cout << "Total profit (greedy 0-1) = " << totalProfit << endl;
    return 0;
}
