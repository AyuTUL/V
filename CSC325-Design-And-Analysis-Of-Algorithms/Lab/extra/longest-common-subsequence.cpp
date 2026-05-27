#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string lcs(string s1, string s2)
{
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> dp(m + 1,
                           vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);

    int i = m;
    int j = n;

    string lcsString = "";

    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcsString += s1[i - 1];

            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    reverse(lcsString.begin(),
            lcsString.end());

    cout << endl
         << "Length of LCS = "
         << dp[m][n] << endl;

    return lcsString;
}

int main()
{
    string s1, s2;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    cout << endl
         << "---Longest Common Subsequence---" << endl;
    string ans = lcs(s1, s2);
    cout << "LCS String = "
         << ans << endl;

    return 0;
}