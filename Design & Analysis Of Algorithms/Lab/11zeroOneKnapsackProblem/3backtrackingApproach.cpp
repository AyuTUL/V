// Lab 11.3: Implement 0-1 Knapsack using Backtracking approach.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Item
{
    int id, profit, weight;
    double ratio;
};

struct Selection
{
    int id, profit, weight;
    int totalWeight, totalProfit, remaining;
};

int n, capacity, bestProfit = 0;
vector<Item> items;
vector<int> includeItem, bestSet;

void border(bool wide)
{
    cout << (wide ? "+------+------------+------------+--------------+--------------+----------------+"
                  : "+------+------------+------------+----------+")
         << endl;
}

void printRow(const Item &it)
{
    cout << left << fixed << setprecision(2)
         << "| " << setw(4) << it.id
         << " | " << setw(10) << it.profit
         << " | " << setw(10) << it.weight
         << " | " << setw(8) << it.ratio << " |" << endl;
    border(false);
}

void printRow(const Selection &s)
{
    cout << left << fixed << setprecision(2)
         << "| " << setw(4) << s.id
         << " | " << setw(10) << s.profit
         << " | " << setw(10) << s.weight
         << " | " << setw(12) << s.totalWeight
         << " | " << setw(12) << s.totalProfit
         << " | " << setw(14) << s.remaining << " |" << endl;
    border(true);
}

double boundValue(int idx, int curW, int curP)
{
    if (curW >= capacity)
        return curP;

    double bound = curP;
    int tw = curW;
    for (int i = idx + 1; i < n; i++)
    {
        if (tw + items[i].weight <= capacity)
        {
            tw += items[i].weight;
            bound += items[i].profit;
        }
        else
        {
            bound += (capacity - tw) * items[i].ratio;
            break;
        }
    }
    return bound;
}

void knapsack(int idx, int curW, int curP)
{
    if (curW > capacity)
        return;

    if (curP > bestProfit)
    {
        bestProfit = curP;
        bestSet = includeItem;
    }

    if (idx == n - 1 || boundValue(idx, curW, curP) <= bestProfit)
        return;

    int next = idx + 1;
    if (curW + items[next].weight <= capacity)
    {
        includeItem[next] = 1;
        knapsack(next, curW + items[next].weight, curP + items[next].profit);
    }

    includeItem[next] = 0;
    knapsack(next, curW, curP);
}

int main()
{
    cout << "Enter number of items : ";
    cin >> n;
    if (n <= 0)
        return cout << "Number of items must be greater than 0." << endl, 0;

    items.resize(n);
    includeItem.assign(n, 0);
    bestSet.assign(n, 0);

    cout << "Enter profit and weight for each item :" << endl;
    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        cout << "Item " << items[i].id << " : ";
        cin >> items[i].profit >> items[i].weight;
        if (items[i].weight <= 0)
            return cout << "Weight must be greater than 0." << endl, 0;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    if (capacity < 0)
        return cout << "Capacity cannot be negative." << endl, 0;

    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.ratio > b.ratio; });

    knapsack(-1, 0, 0);

    int totalProfit = 0, totalWeight = 0;
    vector<Selection> selected;
    for (int i = 0; i < n; i++)
        if (bestSet[i] == 1)
        {
            totalWeight += items[i].weight;
            totalProfit += items[i].profit;
            selected.push_back({items[i].id, items[i].profit, items[i].weight,
                                totalWeight, totalProfit, capacity - totalWeight});
        }

    cout << endl
         << "---0-1 Knapsack Problem using Backtracking Approach---" << endl
         << endl
         << "Items Sorted by Value per Unit Weight :" << endl;
    ;
    border(false);
    cout << "| Item | Profit     | Weight     | P/W      |" << endl;
    border(false);
    for (int i = 0; i < n; i++)
        printRow(items[i]);

    cout << endl
         << "Selected Items :" << endl;
    border(true);
    cout << "| Item | Profit     | Weight     | Total Weight | Total Profit | Remaining Cap. |" << endl;
    border(true);
    if (selected.empty())
    {
        cout << "| " << setw(76) << left << "No items selected." << "|" << endl;
        border(true);
    }
    else
        for (int i = 0; i < (int)selected.size(); i++)
            printRow(selected[i]);

    cout << endl
         << "Maximum Profit = " << bestProfit;
    return 0;
}