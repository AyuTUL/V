// Lab 11.3: Implement 0-1 Knapsack using Backtracking approach.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
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

double boundValue(const vector<Item> &items, int n, int capacity, int idx, int curWeight, int curProfit)
{
    if (curWeight >= capacity)
        return curProfit;
    double bound = curProfit;
    int totalWeight = curWeight;
    for (int i = idx + 1; i < n; i++)
    {
        if (totalWeight + items[i].weight <= capacity)
        {
            totalWeight += items[i].weight;
            bound += items[i].profit;
        }
        else
        {
            bound += (capacity - totalWeight) * items[i].ratio;
            break;
        }
    }
    return bound;
}

void solveKnapsack(int idx, int curWeight, int curProfit,
                   const vector<Item> &items, int n, int capacity,
                   vector<int> &includeItem, vector<int> &bestSet, int &bestProfit)
{
    if (curWeight > capacity)
        return;
    if (curProfit > bestProfit)
    {
        bestProfit = curProfit;
        bestSet = includeItem;
    }
    if (idx == n - 1 || boundValue(items, n, capacity, idx, curWeight, curProfit) <= bestProfit)
        return;
    int next = idx + 1;
    if (curWeight + items[next].weight <= capacity)
    {
        includeItem[next] = 1;
        solveKnapsack(next, curWeight + items[next].weight, curProfit + items[next].profit,
                      items, n, capacity, includeItem, bestSet, bestProfit);
    }
    includeItem[next] = 0;
    solveKnapsack(next, curWeight, curProfit,
                  items, n, capacity, includeItem, bestSet, bestProfit);
}

pair<vector<int>, int> knapsackBacktracking(const vector<Item> &items, int capacity)
{
    int n = static_cast<int>(items.size());
    int bestProfit = 0;
    vector<int> includeItem(n, 0);
    vector<int> bestSet(n, 0);
    solveKnapsack(-1, 0, 0, items, n, capacity, includeItem, bestSet, bestProfit);
    return {bestSet, bestProfit};
}

int main()
{
    int n, capacity;
    cout << "Enter number of items : ";
    cin >> n;
    vector<Item> items(n);
    cout << "Enter profit and weight for each item :" << endl;
    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        cout << "Item " << items[i].id << " : ";
        cin >> items[i].profit >> items[i].weight;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }
    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.ratio > b.ratio; });
    pair<vector<int>, int> result = knapsackBacktracking(items, capacity);
    vector<int> bestSet = result.first;
    int bestProfit = result.second;
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