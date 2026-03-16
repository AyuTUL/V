// Lab 11: Kruskal's Algorithm (Minimum Spanning Tree)
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int u;
    int v;
    int w;
};

struct DSU
{
    vector<int> parent;
    vector<int> rankv;

    DSU(int n) : parent(n + 1), rankv(n + 1, 0)
    {
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int findSet(int x)
    {
        if (parent[x] == x)
            return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }

    bool unionSet(int a, int b)
    {
        a = findSet(a);
        b = findSet(b);

        if (a == b)
            return false;

        if (rankv[a] < rankv[b])
            swap(a, b);

        parent[b] = a;
        if (rankv[a] == rankv[b])
            rankv[a]++;

        return true;
    }
};

bool compareEdges(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}

int main()
{
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    if (n <= 0 || m < 0)
    {
        cout << "Invalid input." << endl;
        return 0;
    }

    vector<Edge> edges(m);
    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    vector<Edge> mst;
    int totalWeight = 0;

    for (int i = 0; i < m; i++)
    {
        if (dsu.unionSet(edges[i].u, edges[i].v))
        {
            mst.push_back(edges[i]);
            totalWeight += edges[i].w;
        }
    }

    if ((int)mst.size() != n - 1)
    {
        cout << "Graph is not connected; MST does not exist." << endl;
        return 0;
    }

    cout << "\nEdges in MST:" << endl;
    for (int i = 0; i < (int)mst.size(); i++)
        cout << mst[i].u << " - " << mst[i].v << " : " << mst[i].w << endl;

    cout << "Total MST weight = " << totalWeight << endl;
    return 0;
}
