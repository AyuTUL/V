// Lab 7.2: Implement merge sort algorithm using divide & conquer.
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Info
{
    int l, h;
};
vector<vector<Info>> lvls;
vector<vector<int>> states;

void printLevel(int a[], int lvl)
{
    if (lvl >= static_cast<int>(lvls.size()))
        return;
    cout << "Level " << lvl << " :" << endl;
    for (int p = 0; p < 3; p++)
    {
        for (int i = 0; i < static_cast<int>(lvls[lvl].size()); i++)
        {
            const Info &segment = lvls[lvl][i];
            cout << (p == 1 ? "|" : "+");
            for (int j = segment.l; j <= segment.h; j++)
                p == 1 ? cout << setw(3) << a[j] << " |" : cout << "----+";
            if (i < static_cast<int>(lvls[lvl].size()) - 1)
                cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

void printMergeLevel(int lvl)
{
    if (lvl >= static_cast<int>(states.size()))
        return;
    cout << "Level " << states.size() - lvl - 1 << " :" << endl;
    int levelIndex = static_cast<int>(lvls.size()) - 1 - lvl;
    for (int p = 0; p < 3; p++)
    {
        for (int i = 0; i < static_cast<int>(lvls[levelIndex].size()); i++)
        {
            const Info &segment = lvls[levelIndex][i];
            cout << (p == 1 ? "|" : "+");
            for (int j = segment.l; j <= segment.h; j++)
                p == 1 ? cout << setw(3) << states[lvl][j] << " |" : cout << "----+";
            if (i < static_cast<int>(lvls[levelIndex].size()) - 1)
                cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

void merge(int a[], int l, int m, int h)
{
    int n1 = m - l + 1;
    int n2 = h - m;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = a[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void build(int a[], int n)
{
    lvls.clear();
    lvls.push_back({{0, n - 1}});
    for (int lvl = 0;; lvl++)
    {
        vector<Info> next;
        bool split = false;
        for (const auto &range : lvls[lvl])
            if (range.l >= range.h)
                next.push_back({range.l, range.h});
            else
            {
                int mid = (range.l + range.h) / 2;
                next.push_back({range.l, mid});
                next.push_back({mid + 1, range.h});
                split = true;
            }
        if (!split)
            break;
        lvls.push_back(next);
    }
    states.clear();
    vector<int> st(a, a + n);
    for (int lvl = static_cast<int>(lvls.size()) - 1; lvl >= 0; lvl--)
    {
        states.push_back(st);
        if (lvl > 0)
            for (const auto &parent : lvls[lvl - 1])
                if (parent.l < parent.h)
                {
                    int mid = (parent.l + parent.h) / 2;
                    merge(&st[0], parent.l, mid, parent.h);
                }
    }
}

int main()
{
    int n;
    cout << "Enter array size : ";
    cin >> n;
    int *a = new int[n], *o = new int[n];
    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        o[i] = a[i];
    }
    cout << endl
         << "---Merge Sort using Divide & Conquer---" << endl
         << endl;
    build(a, n);
    for (int i = 0; i < static_cast<int>(lvls.size()); i++)
        printLevel(o, i);
    for (int i = 1; i < static_cast<int>(states.size()); i++)
        printMergeLevel(i);
    cout << "Final Sorted Array :" << endl;
    for (int i = 0; i < n; i++)
        cout << states.back()[i] << " ";
    delete[] a;
    delete[] o;
    return 0;
}