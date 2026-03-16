// Lab 12: 0-1 Knapsack using Dynamic Programming
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

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

    vector<int> profit(n + 1), weight(n + 1);

    cout << "Enter profit and weight for each item:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "Item " << i << ": ";
        cin >> profit[i] >> weight[i];

        if (weight[i] <= 0)
        {
            cout << "Weight must be greater than 0." << endl;
            return 0;
        }
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0)
    {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (weight[i] <= w)
                dp[i][w] = max(dp[i - 1][w], profit[i] + dp[i - 1][w - weight[i]]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "\nMaximum profit (DP) = " << dp[n][capacity] << endl;

    vector<int> selected;
    int w = capacity;
    for (int i = n; i >= 1; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(i);
            w -= weight[i];
        }
    }

    cout << "Selected items:" << endl;
    for (int i = (int)selected.size() - 1; i >= 0; i--)
        cout << "Item " << selected[i] << " (p=" << profit[selected[i]] << ", w=" << weight[selected[i]] << ")" << endl;

    return 0;
}
