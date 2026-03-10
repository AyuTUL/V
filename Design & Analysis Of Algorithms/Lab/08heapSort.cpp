// Lab 8: WAP to implement heap sort.
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void printTree(int a[], int n)
{
    if (n <= 0)
        return;

    int h = log2(n) + 1, node_len = 1;

    for (int i = 0; i < n; i++)
        node_len = max(node_len, (int)to_string(a[i]).length());

    int space_len = node_len % 2 ? 3 : 4;
    int node_shift = node_len / 2;
    int space_shift = space_len / 2;

    for (int lv = 0; lv < h; lv++)
    {
        int nodes = 1 << lv;
        int leaf_nodes = 1 << (h - lv - 1);

        int w = node_len * leaf_nodes + space_len * (leaf_nodes - 1);
        int indent = w / 2 - node_shift;
        int spacing = w - 2 * (node_shift - space_shift);

        cout << string(indent, ' ');

        for (int i = 0; i < nodes; i++)
        {
            int idx = nodes - 1 + i;

            if (idx < n)
                cout << setw(node_len) << a[idx];
            else
                cout << string(node_len, ' ');

            if (i < nodes - 1)
                cout << string(spacing, ' ');
        }
        cout << endl;

        if (lv == h - 1)
            continue;

        int branch_rows = (w + 1) / 4;

        for (int r = 0; r < branch_rows; r++)
        {
            cout << string(w / 2 - 1 - r, ' ');

            for (int i = 0; i < nodes; i++)
            {
                int idx = nodes - 1 + i;

                if (idx < n)
                {
                    int L = (1 << (lv + 1)) - 1 + 2 * i;
                    int R = L + 1;

                    cout << (L < n ? '/' : ' ');
                    cout << string((node_len % 2) + 2 * r, ' ');
                    cout << (R < n ? '\\' : ' ');
                }
                else
                    cout << string((node_len % 2) + 2 * r + 2, ' ');

                if (i < nodes - 1)
                    cout << string(spacing + 2 * (node_shift - 1 - r), ' ');
            }
            cout << endl;
        }
    }
    cout << endl;
}

void heapify(int a[], int n, int i)
{
    int l = 2 * i + 1, r = 2 * i + 2, largest = i;

    if (l < n && a[l] > a[largest])
        largest = l;
    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i)
    {
        cout << "Swap node " << a[i] << " with " << a[largest] << endl;
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    cout << "Building Max Heap" << endl;

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    cout << endl
         << "Max Heap Tree :" << endl;
    printTree(a, n);

    for (int i = n - 1; i > 0; i--)
    {
        cout << "--------------------------------" << endl
             << " Swap root " << a[0] << " with last node " << a[i] << endl;

        swap(a[0], a[i]);

        cout << "Node removed (sorted) : " << a[i] << endl
             << endl
             << "Tree before heapify :" << endl;
        printTree(a, i);

        heapify(a, i, 0);

        cout << "Tree after heapify :" << endl;
        printTree(a, i);
    }
}

int main()
{
    int n;
    cout << "Enter number of elements : ";
    cin >> n;

    int *a = new int[n];

    cout << "Enter elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << endl
         << "---Heap Sort Algorithm---" << endl;

    cout << endl
         << "Original Tree :" << endl;
    printTree(a, n);

    heapSort(a, n);

    cout << endl
         << "Final Sorted Array :";
    for (int i = 0; i < n; i++)
        cout << " " << a[i];

    delete[] a;
}