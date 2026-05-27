#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int minimum(int a, int b, int c)
{
    return min(min(a, b), c);
}

int editDistance(string str1, string str2)
{
    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> dp(m + 1,
                           vector<int>(n + 1));

    for (int i = 0; i <= m; i++)
    {

        for (int j = 0; j <= n; j++)
        {

            if (i == 0)
                dp[i][j] = j;

            else if (j == 0)
                dp[i][j] = i;

            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            else
            {

                dp[i][j] =
                    1 + minimum(
                            dp[i][j - 1],
                            dp[i - 1][j],
                            dp[i - 1][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;

    cout << "Enter second string: ";
    cin >> str2;

    int result =
        editDistance(str1, str2);

    cout << endl
         << "---Minimum Edit Distance---" << endl;
    cout << endl
         << "Minimum Edit Distance = "
         << result << endl;

    return 0;
}