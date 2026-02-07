// Lab 7.3: WAP to implement Quick Sort using divide & conquer.
#include <iostream>
using namespace std;

int partition(int a[], int low, int high)
{
    int pivot = a[high];      // pivot element
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n;
    cout << "--- Quick Sort using Divide and Conquer ---" << endl;

    cout << "Enter array size : ";
    cin >> n;

    int *a = new int[n];

    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    quickSort(a, 0, n - 1);

    cout << "\nSorted array : ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    delete[] a;
    return 0;
}
