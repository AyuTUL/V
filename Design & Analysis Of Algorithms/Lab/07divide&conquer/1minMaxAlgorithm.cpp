// Lab 7.1: Implement Min-Max algorithm using divide & conquer.
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

struct Info
{
    int l, h, mn, mx;
};

vector<vector<Info>> lvls, conq;

void printLevel(int a[], int lvl)
{
    if (lvl >= static_cast<int>(lvls.size()))
        return;
    cout << "Level " << lvl << " :" << endl;
    for (int pass = 0; pass < 3; pass++)
    {
        for (int i = 0; i < static_cast<int>(lvls[lvl].size()); i++)
        {
            const Info &segment = lvls[lvl][i];
            if (pass == 1)
            {
                cout << "|";
                for (int j = segment.l; j <= segment.h; j++)
                    cout << setw(3) << a[j] << " |";
            }
            else
            {
                cout << "+";
                for (int j = segment.l; j <= segment.h; j++)
                    cout << "----+";
            }
            if (i < static_cast<int>(lvls[lvl].size()) - 1)
                cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

void printConquerLevel(int lvl)
{
    if (lvl >= static_cast<int>(conq.size()))
        return;
    cout << "Level " << lvl << " :" << endl;
    for (int i = 0; i < static_cast<int>(conq[lvl].size()); i++)
    {
        cout << "Min =" << conq[lvl][i].mn << " Max =" << conq[lvl][i].mx;
        if (i < static_cast<int>(conq[lvl].size()) - 1)
            cout << "     ";
    }
    cout << endl
         << endl;
}

void build(int a[], int n)
{
    lvls.clear();
    lvls.push_back({{0, n - 1, 0, 0}});
    for (int lvl = 0;; lvl++)
    {
        vector<Info> next;
        bool split = false;
        for (const auto &range : lvls[lvl])
            if (range.l >= range.h - 1)
                next.push_back({range.l, range.h, 0, 0});
            else
            {
                int mid = (range.l + range.h) / 2;
                next.push_back({range.l, mid, 0, 0});
                next.push_back({mid + 1, range.h, 0, 0});
                split = true;
            }
        if (!split)
            break;
        lvls.push_back(next);
    }
    conq = lvls;
    for (auto &range : conq.back())
    {
        range.mn = a[range.l];
        range.mx = a[range.l];
        if (range.l < range.h)
        {
            range.mn = min(a[range.l], a[range.h]);
            range.mx = max(a[range.l], a[range.h]);
        }
    }
    for (int lvl = static_cast<int>(lvls.size()) - 2; lvl >= 0; lvl--)
    {
        for (auto &parent : conq[lvl])
        {
            int mid = (parent.l + parent.h) / 2;
            int leftIndex = -1, rightIndex = -1;

            for (int j = 0; j < static_cast<int>(conq[lvl + 1].size()); j++)
            {
                const Info &child = conq[lvl + 1][j];
                if (child.l == parent.l && child.h <= mid)
                    leftIndex = j;
                else if (child.l > mid && child.h == parent.h)
                    rightIndex = j;
            }
            if (leftIndex != -1 && rightIndex != -1)
            {
                parent.mn = min(conq[lvl + 1][leftIndex].mn, conq[lvl + 1][rightIndex].mn);
                parent.mx = max(conq[lvl + 1][leftIndex].mx, conq[lvl + 1][rightIndex].mx);
            }
            else
            {
                parent.mn = a[parent.l];
                parent.mx = a[parent.l];
                for (int i = parent.l + 1; i <= parent.h; i++)
                {
                    parent.mn = min(parent.mn, a[i]);
                    parent.mx = max(parent.mx, a[i]);
                }
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter array size : ";
    cin >> n;
    int *a = new int[n];
    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << endl
         << "---Min-Max Algorithm using Divide & Conquer---" << endl
         << endl;
    build(a, n);
    for (int i = 0; i < static_cast<int>(lvls.size()); i++)
        printLevel(a, i);
    for (int i = static_cast<int>(conq.size()) - 1; i >= 0; i--)
        printConquerLevel(i);
    cout << "Final Result :" << endl
         << "Minimum element = " << conq[0][0].mn << endl
         << "Maximum element = " << conq[0][0].mx;
    delete[] a;
    return 0;
}