// Lab 11.2: Implement 0-1 Knapsack using Dynamic Programming.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Selection
{
    int id, profit, weight;
    int totalWeight, totalProfit, remaining;
};

void border(bool wide)
{
    cout << (wide ? "+------+------------+------------+--------------+--------------+----------------+"
                  : "+------+------------+------------+")
         << endl;
}

void printLine(int cols, int width)
{
    cout << "+";
    for (int c = 0; c < cols; c++)
    {
        for (int k = 0; k < width; k++)
            cout << "-";
        cout << "+";
    }
    cout << endl;
}

void printDPTable(const vector<vector<int>> &dp, int n, int capacity)
{
    const int w = 4;
    cout << "Dynamic Programming Table :" << endl;
    printLine(capacity + 2, w + 1);
    cout << "| " << setw(w) << left << "i\\W";
    for (int c = 0; c <= capacity; c++)
        cout << "|  " << setw(w - 1) << left << c;
    cout << "|" << endl;
    printLine(capacity + 2, w + 1);
    for (int i = 0; i <= n; i++)
    {
        cout << "|  " << setw(w - 1) << left << i;
        for (int c = 0; c <= capacity; c++)
            cout << "|  " << setw(w - 1) << left << dp[i][c];
        cout << "|" << endl;
    }
    printLine(capacity + 2, w + 1);
}

void printRow(const Selection &s)
{
    cout << left
         << "| " << setw(4) << s.id
         << " | " << setw(10) << s.profit
         << " | " << setw(10) << s.weight
         << " | " << setw(12) << s.totalWeight
         << " | " << setw(12) << s.totalProfit
         << " | " << setw(14) << s.remaining << " |" << endl;
    border(true);
}

void printSelectedTable(const vector<int> &selected, const vector<int> &profit, const vector<int> &weight, int capacity)
{
    cout << endl
         << "Selected Items :" << endl;
    border(true);
    cout << "| Item | Profit     | Weight     | Total Weight | Total Profit | Remaining Cap. |" << endl;
    border(true);
    if (selected.empty())
    {
        cout << "| " << setw(76) << left << "None" << "|" << endl;
        border(true);
        return;
    }
    int totalWeight = 0, totalProfit = 0;
    for (int i = 0; i < (int)selected.size(); i++)
    {
        int id = selected[i];
        totalWeight += weight[id];
        totalProfit += profit[id];
        Selection row = {id, profit[id], weight[id], totalWeight, totalProfit, capacity - totalWeight};
        printRow(row);
    }
}

vector<vector<int>> buildDPTable(const vector<int> &profit, const vector<int> &weight, int n, int capacity)
{
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= capacity; w++)
            dp[i][w] = (weight[i] <= w) ? max(dp[i - 1][w], profit[i] + dp[i - 1][w - weight[i]]) : dp[i - 1][w];
    return dp;
}

vector<int> getSelectedItems(const vector<vector<int>> &dp, const vector<int> &weight, int n, int capacity)
{
    vector<int> selected;
    int w = capacity;

    for (int i = n; i >= 1; i--)
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(i);
            w -= weight[i];
        }
    reverse(selected.begin(), selected.end());
    return selected;
}

int main()
{
    int n, capacity;
    cout << "Enter number of items : ";
    cin >> n;
    vector<int> profit(n + 1), weight(n + 1);
    cout << "Enter profit and weight for each item :" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "Item " << i << ": ";
        cin >> profit[i] >> weight[i];
    }
    cout << "Enter knapsack capacity : ";
    cin >> capacity;
    cout << endl
         << "---0-1 Knapsack Problem using Dynamic Programming---" << endl
         << endl;
    vector<vector<int>> dp = buildDPTable(profit, weight, n, capacity);
    printDPTable(dp, n, capacity);
    vector<int> selected = getSelectedItems(dp, weight, n, capacity);
    printSelectedTable(selected, profit, weight, capacity);
    cout << endl
         << "Maximum Profit = " << dp[n][capacity];
    return 0;
}