#include <climits>
#include <iostream>
#include <vector>
using namespace std;

void printParenthesis(vector<vector<int>> &bracket, int i, int j, char &name)
{
    if (i == j)
    {
        cout << name++;
        return;
    }
    cout << "(";
    printParenthesis(bracket, i, bracket[i][j], name);
    printParenthesis(bracket, bracket[i][j] + 1, j, name);
    cout << ")";
}

int matrixChainOrder(vector<int> &arr, int n, vector<vector<int>> &bracket)
{
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int length = 2; length < n; length++)
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }
    return dp[1][n - 1];
}

int main()
{
    int n;

    cout << "Enter number of matrices : ";
    cin >> n;
    vector<int> arr(n + 1);
    cout << endl
         << "Enter dimensions array:" << endl;
    for (int i = 0; i <= n; i++)
    {
        cin >> arr[i];
    }
    vector<vector<int>> bracket(n + 1, vector<int>(n + 1, 0));
    int minCost = matrixChainOrder(arr, n + 1, bracket);
    cout << endl
         << "---Matrix Chain Multiplication---" << endl;
    cout << endl
         << "Minimum multiplications = " << minCost << endl;
    cout << "Optimal Parenthesization = ";
    char name = 'A';
    printParenthesis(bracket, 1, n, name);
    cout << endl;
    return 0;
}