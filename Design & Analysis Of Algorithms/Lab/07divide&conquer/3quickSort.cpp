// Lab 7.3: Implement quick sort algorithm using divide & conquer.
#include <iostream>
#include <iomanip>
using namespace std;

void printArray(int a[], int n, int L = -1, int R = -1, bool showPivot = 0, int pivot = -1)
{
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << setw(6) << right << i;
    cout << endl
         << "      ";
    for (int i = 0; i < n; i++)
        cout << "+-----";
    cout << "+" << endl
         << "      | ";
    for (int i = 0; i < n; i++)
        cout << setw(3) << left << a[i] << " | ";
    cout << right << endl
         << "      ";
    for (int i = 0; i < n; i++)
        cout << "+-----";
    cout << "+" << endl;
    if (L != -1 || R != -1)
    {
        cout << "      ";
        int dL = L >= n ? n - 1 : L;
        for (int i = 0; i < n; i++)
            cout << (i == dL && i == R ? "  L,R " : i == dL ? "   L  "
                                                : i == R    ? "   R  "
                                                            : "      ");
    }
    cout << endl;
    if (showPivot && pivot != -1)
        cout << endl
             << "Pivot = " << pivot << ". L and R are pointing at beginning and end of array";
    cout << endl;
}

int partition(int a[], int low, int high, int n)
{
    int pivot = a[low], L = low, R = high;
    cout << "Pivot element = " << pivot << " [" << low << "]" << endl
         << endl
         << "Initial state :" << endl;
    printArray(a, n, L, R, 1, pivot);
    while (1)
    {
        cout << "L[" << L << "] < R[" << R << "]" << endl
             << "Increment L till a[L] <= pivot " << endl
             << "Decrement R till a[R] > " << pivot << endl;
        while (L <= high && a[L] <= pivot)
            L++;
        while (R > low && a[R] > pivot)
            R--;
        printArray(a, n, L, R);
        if (L < R)
        {
            cout << "L < R, swap " << a[L] << " & " << a[R] << endl;
            swap(a[L], a[R]);
            printArray(a, n, L, R);
        }
        else
        {
            cout << "L >= R, partitioning complete." << endl;
            break;
        }
    }
    swap(a[low], a[R]);
    cout << "After placing pivot in correct index :" << endl;
    printArray(a, n);
    cout << "Partition complete around pivot " << pivot << " at index " << R << endl
         << string(50, '-') << endl;
    return R;
}

void quickSort(int a[], int low, int high, int n)
{
    if (low >= high)
        return;
    int p = partition(a, low, high, n);
    if (low < p - 1)
    {
        cout << "Recursively sorting left subarray [" << low << ", " << p - 1 << "]" << endl;
        quickSort(a, low, p - 1, n);
    }
    if (p + 1 < high)
    {
        cout << "Recursively sorting right subarray [" << p + 1 << ", " << high << "]" << endl;
        quickSort(a, p + 1, high, n);
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
         << "---Quick Sort using Divide & Conquer---" << endl
         << endl;
    quickSort(a, 0, n - 1, n);
    cout << "Final Sorted Array :" << endl;
    printArray(a, n);
    delete[] a;
}