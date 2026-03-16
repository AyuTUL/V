// Lab 10.1: WAP to implement Kruskal's Algorithm for Minimum Spanning Tree.
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    char u, v;
    int w;
};

struct DSU
{
    vector<int> parent, rank_;
    DSU() : parent(26), rank_(26, 0)
    {
        for (int i = 0; i < 26; i++)
            parent[i] = i;
    }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (rank_[a] < rank_[b])
            swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b])
            rank_[a]++;
        return true;
    }
};

void border() { cout << "+--------+--------+--------+" << endl; }

void printRow(char u, char v, int w)
{
    cout << "|   " << left << setw(2) << u << "   |   " << setw(2) << v << "   |   " << setw(5) << w << "|" << endl;
}

int main()
{
    int n, m;
    cout << "Enter vertices and edges: ";
    cin >> n >> m;
    if (n <= 0 || n > 26 || m < 0)
        return cout << "Invalid input. Use 1-26 vertices and non-negative edges." << endl,
               0;

    vector<Edge> edges(m);
    cout << "Enter edges (u v w) :" << endl;
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.w < b.w; });

    DSU dsu;
    int totalCost = 0, edgeCount = 0;

    cout << endl
         << "---Kruskal's Algorithm for Minimum Spanning Tree---" << endl
         << endl;
    border();
    cout << "| Edge 1 | Edge 2 | Weight |" << endl;
    border();

    for (auto &e : edges)
    {
        int u = toupper((unsigned char)e.u) - 'A';
        int v = toupper((unsigned char)e.v) - 'A';
        if (u < 0 || u >= 26 || v < 0 || v >= 26)
        {
            cout << endl
                 << "Invalid vertex label found. Use letters A-Z." << endl;
            return 0;
        }
        if (dsu.unite(u, v))
        {
            printRow(e.u, e.v, e.w);
            totalCost += e.w;
            edgeCount++;
        }
    }

    border();
    if (edgeCount != n - 1)
        return cout << endl
                    << "Graph is not connected; MST doesn't exist." << endl,
               0;
    cout << endl
         << "Minimum Cost = " << totalCost;
    return 0;
}