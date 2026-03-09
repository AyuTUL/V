// Lab 8: WAP to implement heap sort.
#include <iostream>
#include <cmath>
using namespace std;

void printTree(int a[], int n)
{
    int height = floor(log2(n)) + 1;
    int maxWidth = pow(2, height);

    int index = 0;

    for (int level = 0; level < height; level++)
    {
        int nodes = pow(2, level);
        int gap = maxWidth / nodes;

        // print nodes
        for (int i = 0; i < nodes && index < n; i++)
        {
            cout << string(gap / 2, ' ');
            cout << a[index++];
            cout << string(gap / 2, ' ');
        }
        cout << endl;

        // print edges
        if (level < height - 1)
        {
            index -= nodes;

            for (int i = 0; i < nodes && index < n; i++)
            {
                cout << string(gap / 2 - 1, ' ');

                if (2 * index + 1 < n)
                    cout << "/";
                else
                    cout << " ";

                cout << " ";

                if (2 * index + 2 < n)
                    cout << "\\";
                else
                    cout << " ";

                cout << string(gap / 2 - 1, ' ');

                index++;
            }
            cout << endl;
        }
    }

    cout << endl;
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        cout << "Swap node " << a[i] << " with " << a[largest] << endl;
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    cout << "Building Max Heap\n";

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    cout << "\nMax Heap Tree:\n";
    printTree(a, n);

    for (int i = n - 1; i > 0; i--)
    {
        cout << "--------------------------------\n";
        cout << "Swap root " << a[0] << " with last node " << a[i] << endl;

        swap(a[0], a[i]);

        cout << "Node removed (sorted): " << a[i] << endl;

        cout << "\nTree before heapify:\n";
        printTree(a, i);

        heapify(a, i, 0);

        cout << "Tree after heapify:\n";
        printTree(a, i);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int a[n];

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "\nOriginal Tree:\n";
    printTree(a, n);

    heapSort(a, n);

    cout << "\nFinal Sorted Array:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}