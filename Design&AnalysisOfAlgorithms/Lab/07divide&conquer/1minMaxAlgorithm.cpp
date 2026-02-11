#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Info
{
    int l, h, mn, mx;
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
        cout << "Min=" << conq[lvl][i].mn << " Max=" << conq[lvl][i].mx << (i < conq[lvl].size() - 1 ? "     " : "");
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
        for (auto &r : lvls[lvl])
            if (r.l >= r.h - 1)
                next.push_back({r.l, r.h, 0, 0});
            else
            {
                int m = (r.l + r.h) / 2;
                next.push_back({r.l, m, 0, 0});
                next.push_back({m + 1, r.h, 0, 0});
                split = true;
            }
        if (!split)
            break;
        lvls.push_back(next);
    }
    conq = lvls;
    for (auto &r : conq.back())
        r.mn = r.mx = a[r.l], r.mn = (r.l < r.h ? min(a[r.l], a[r.h]) : r.mn), r.mx = (r.l < r.h ? max(a[r.l], a[r.h]) : r.mx);
    for (int lvl = lvls.size() - 2; lvl >= 0; lvl--)
        for (auto &p : conq[lvl])
        {
            int m = (p.l + p.h) / 2, li = -1, ri = -1;
            for (int j = 0; j < conq[lvl + 1].size(); j++)
                (conq[lvl + 1][j].l == p.l && conq[lvl + 1][j].h <= m) ? li = j : (conq[lvl + 1][j].l > m && conq[lvl + 1][j].h == p.h) ? ri = j
                                                                                                                                        : 0;
            if (li != -1 && ri != -1)
                p.mn = min(conq[lvl + 1][li].mn, conq[lvl + 1][ri].mn), p.mx = max(conq[lvl + 1][li].mx, conq[lvl + 1][ri].mx);
            else
            {
                p.mn = p.mx = a[p.l];
                for (int i = p.l + 1; i <= p.h; i++)
                    p.mn = min(p.mn, a[i]), p.mx = max(p.mx, a[i]);
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
         << "--- Min-Max Algorithm using Divide & Conquer---" << endl
         << endl;
    build(a, n);
    for (int i = 0; i < lvls.size(); i++)
        printLevel(a, i);
    for (int i = conq.size() - 1; i >= 0; i--)
        printConquerLevel(i);
    cout << "Final Result :" << endl
         << "Minimum element = " << conq[0][0].mn << endl
         << "Maximum element = " << conq[0][0].mx;
    delete[] a;
}
