#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct MinMax
{
    int min, max;
};
struct Info
{
    int l, h, min, max;
};

vector<vector<Info>> lvls, conq;

void printLevel(int a[], int lvl)
{
    if (lvl >= lvls.size())
        return;
    cout << "Level " << lvl << " :" << endl;
    for (int pass = 0; pass < 3; pass++)
    {
        for (int i = 0; i < lvls[lvl].size(); i++)
        {
            auto &x = lvls[lvl][i];
            if (pass == 1)
            {
                cout << "|";
                for (int j = x.l; j <= x.h; j++)
                    cout << setw(3) << a[j] << " |";
            }
            else
            {
                cout << "+";
                for (int j = x.l; j <= x.h; j++)
                    cout << "----+";
            }
            if (i < lvls[lvl].size() - 1)
                cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

void printConquerLevel(int lvl)
{
    if (lvl >= conq.size())
        return;
    cout << "Level " << lvl << " :" << endl;
    for (int i = 0; i < conq[lvl].size(); i++)
    {
        auto &x = conq[lvl][i];
        cout << "Min=" << x.min << " Max=" << x.max;
        if (i < conq[lvl].size() - 1)
            cout << "     ";
    }
    cout << endl
         << endl;
}

MinMax findMinMax(int a[], int l, int h, int lvl = 0)
{
    if (lvl >= lvls.size())
        lvls.resize(lvl + 1);
    lvls[lvl].push_back({l, h, 0, 0});

    MinMax r;
    if (l == h)
        r = {a[l], a[l]};
    else if (h == l + 1)
        r = {min(a[l], a[h]), max(a[l], a[h])};
    else
    {
        int m = (l + h) / 2;
        auto L = findMinMax(a, l, m, lvl + 1);
        auto R = findMinMax(a, m + 1, h, lvl + 1);
        r = {min(L.min, R.min), max(L.max, R.max)};
    }

    if (lvl >= conq.size())
        conq.resize(lvl + 1);
    conq[lvl].push_back({l, h, r.min, r.max});
    return r;
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
         << "--- Min-Max Algorithm using Divide & Conquer---" << endl
         << endl;
    MinMax ans = findMinMax(a, 0, n - 1);

    for (int i = 0; i < lvls.size(); i++)
        printLevel(a, i);
    for (int i = conq.size() - 1; i >= 0; i--)
        printConquerLevel(i);

    cout << "Final Result :" << endl
         << "Minimum element = " << ans.min << endl
         << "Maximum element = " << ans.max;

    delete[] a;
    return 0;
}
