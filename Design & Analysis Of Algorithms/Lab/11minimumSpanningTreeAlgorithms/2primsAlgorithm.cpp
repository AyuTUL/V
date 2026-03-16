// Lab 11: Prim's Algorithm (Minimum Spanning Tree)
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of vertices must be greater than 0." << endl;
        return 0;
    }

    vector<vector<int>> cost(n + 1, vector<int>(n + 1));
    cout << "Enter adjacency matrix (0 for no edge):" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> cost[i][j];
            if (i != j && cost[i][j] == 0)
                cost[i][j] = INT_MAX;
        }
    }

    vector<int> key(n + 1, INT_MAX), parent(n + 1, -1);
    vector<bool> inMST(n + 1, false);

    key[1] = 0;

    for (int count = 1; count <= n; count++)
    {
        int u = -1;
        int minKey = INT_MAX;

        for (int v = 1; v <= n; v++)
        {
            if (!inMST[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        inMST[u] = true;

        for (int v = 1; v <= n; v++)
        {
            if (!inMST[v] && cost[u][v] < key[v])
            {
                key[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }

    int totalWeight = 0;
    cout << "\nEdges in MST:" << endl;
    for (int v = 2; v <= n; v++)
    {
        if (parent[v] == -1)
        {
            cout << "Graph is not connected; MST does not exist." << endl;
            return 0;
        }
        cout << parent[v] << " - " << v << " : " << key[v] << endl;
        totalWeight += key[v];
    }

    cout << "Total MST weight = " << totalWeight << endl;
    return 0;
}
