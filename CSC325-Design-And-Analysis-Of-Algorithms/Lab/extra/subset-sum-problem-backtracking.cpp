#include <bits/stdc++.h>
using namespace std;

bool found = false;

// Function to print subsets with given sum
void PrintSubsetSum(int i,
                    int n,
                    vector<int> &arr,
                    int targetSum,
                    vector<int> &subset)
{
    // If target becomes 0, subset found
    if (targetSum == 0)
    {
        found = true;
        cout << "[ ";
        for (int x : subset)
            cout << x << " ";
        cout << "]" << endl;
        return;
    }

    // If end of array reached
    if (i == n)
        return;

    // Exclude current element
    PrintSubsetSum(i + 1, n, arr, targetSum, subset);

    // Include current element if possible
    if (arr[i] <= targetSum)
    {
        subset.push_back(arr[i]);
        PrintSubsetSum(i + 1,
                       n,
                       arr,
                       targetSum - arr[i],
                       subset);
        // Backtrack
        subset.pop_back();
    }
}

int main()
{
    int n;
    cout << "Enter number of elements : ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements :";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int target;
    cout << "Enter target sum: ";
    cin >> target;
    vector<int> subset;
    cout << endl
         << "---Subset Sum Problem using Backtracking---" << endl;
    cout << endl
         << "Subsets with sum "
         << target
         << " are :" << endl;

    PrintSubsetSum(0, n, arr, target, subset);
    if (!found)
        cout << "No subset found.";

    return 0;
}