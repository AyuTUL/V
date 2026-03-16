// Lab 12: 0-1 Knapsack using Backtracking (Branch and Bound style)
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

int n, capacity;
vector<Item> items;
vector<int> includeItem;
vector<int> bestSet;
int bestProfit = 0;

double boundValue(int idx, int currentWeight, int currentProfit)
{
    if (currentWeight >= capacity)
        return currentProfit;

    double bound = currentProfit;
    int totalWeight = currentWeight;

    for (int i = idx + 1; i < n; i++)
    {
        if (totalWeight + items[i].weight <= capacity)
        {
            totalWeight += items[i].weight;
            bound += items[i].profit;
        }
        else
        {
            int remaining = capacity - totalWeight;
            bound += remaining * items[i].ratio;
            break;
        }
    }

    return bound;
}

void knapsack(int idx, int currentWeight, int currentProfit)
{
    if (currentWeight <= capacity && currentProfit > bestProfit)
    {
        bestProfit = currentProfit;
        bestSet = includeItem;
    }

    if (idx == n - 1)
        return;

    double b = boundValue(idx, currentWeight, currentProfit);
    if (b <= bestProfit)
        return;

    includeItem[idx + 1] = 1;
    knapsack(idx + 1,
             currentWeight + items[idx + 1].weight,
             currentProfit + items[idx + 1].profit);

    includeItem[idx + 1] = 0;
    knapsack(idx + 1, currentWeight, currentProfit);
}

int main()
{
    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of items must be greater than 0." << endl;
        return 0;
    }

    items.resize(n);
    includeItem.assign(n, 0);
    bestSet.assign(n, 0);

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

    knapsack(-1, 0, 0);

    cout << "\nMaximum profit (Backtracking) = " << bestProfit << endl;
    cout << "Selected items:" << endl;

    for (int i = 0; i < n; i++)
    {
        if (bestSet[i] == 1)
            cout << "Item " << items[i].id << " (p=" << items[i].profit << ", w=" << items[i].weight << ")" << endl;
    }

    return 0;
}
