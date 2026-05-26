#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

const int INF = 1e8;

void floydWarshall(vector<vector<int>> &dist)
{
    const int V = static_cast<int>(dist.size());
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
        {
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < V; ++j)
            {
                if (dist[k][j] == INF)
                    continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
}

int main()
{
    int V;
    cout << "Enter number of vertices : ";
    cin >> V;
    vector<vector<int>> dist(V, vector<int>(V));
    cout << endl
         << "Enter adjacency matrix (-1 for no edge):" << endl;

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
        {
            int x;
            cin >> x;
            dist[i][j] = (x == -1) ? INF : x;
        }

    floydWarshall(dist);
    cout << endl
         << "---Floyd-Warshall Algorithm---" << endl;
    cout << endl
         << "Shortest distance matrix :" << endl;
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
            cout << setw(6) << (dist[i][j] == INF ? -1 : dist[i][j]);
        cout << endl;
    }
    return 0;
}