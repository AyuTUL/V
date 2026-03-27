// Lab 10.2: WAP to implement Prim's Algorithm for Minimum Spanning Tree.
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void border() { cout << "+--------+--------+--------+" << endl; }

void printRow(char u, char v, int w)
{
    cout << "|   " << left << setw(2) << u << "   |   " << setw(2) << v << "   |   " << setw(5) << w << "|" << endl;
}

pair<vector<int>, vector<int>> prim(const vector<vector<int>> &g)
{
    int n = static_cast<int>(g.size());
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);
    key[0] = 0;
    for (int k = 0; k < n; k++)
    {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        if (u == -1 || key[u] == INT_MAX)
            break;
        inMST[u] = true;
        for (int v = 0; v < n; v++)
            if (!inMST[v] && g[u][v] < key[v])
                key[v] = g[u][v], parent[v] = u;
    }
    return {parent, key};
}

int main()
{
    int n;
    cout << "Enter no. of vertices: ";
    cin >> n;
    vector<char> name(n);
    cout << "Enter " << n << " vertices: ";
    for (int i = 0; i < n; i++)
        cin >> name[i];
    vector<vector<int>> g(n, vector<int>(n));
    cout << "Enter adjacency matrix (-1 for no edge) :" << endl
         << "  ";
    for (int i = 0; i < n; i++)
        cout << "  " << name[i];
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << " " << name[i] << " ";
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
            if (i != j && g[i][j] == -1)
                g[i][j] = INT_MAX;
        }
    }
    pair<vector<int>, vector<int>> result = prim(g);
    vector<int> parent = result.first;
    vector<int> key = result.second;
    int totalCost = 0;
    cout << endl
         << "---Prim's Algorithm for Minimum Spanning Tree---" << endl
         << endl;
    border();
    cout << "| Edge 1 | Edge 2 | Weight |" << endl;
    border();
    for (int v = 1; v < n; v++)
    {
        if (parent[v] == -1)
        {
            border();
            cout << endl
                 << "Graph is not connected; MST doesn't exist." << endl;
            return 0;
        }
        printRow(name[parent[v]], name[v], key[v]);
        totalCost += key[v];
    }
    border();
    cout << endl
         << "Minimum Cost = " << totalCost;
    return 0;
}