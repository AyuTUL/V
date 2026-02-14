// Lab 7.3: WAP to implement Quick Sort using divide & conquer.
#include <iostream>
#include <iomanip>
using namespace std;

void printArray(int a[], int n, int L = -1, int R = -1, bool showPivot = false, int pivot = -1)
{
    // Print array indices
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << setw(6) << i;
    cout << endl;

    // Print top border
    cout << "      ";
    for (int i = 0; i < n; i++)
        cout << "+-----";
    cout << "+" << endl;

    // Print array elements
    cout << "      | ";
    for (int i = 0; i < n; i++)
        cout << setw(3) << left << a[i] << " | ";
    cout << endl;

    // Print bottom border
    cout << "      ";
    for (int i = 0; i < n; i++)
        cout << "+-----";
    cout << "+" << endl;

    // Print L and R indicators
    if (L != -1 || R != -1)
    {
        cout << "      ";
        for (int i = 0; i < n; i++)
        {
            if (i == L && i == R)
                cout << "  L,R ";
            else if (i == L)
                cout << "   L  ";
            else if (i == R)
                cout << "   R  ";
            else
                cout << "      ";
        }
        cout << endl;
    }

    if (showPivot && pivot != -1)
    {
        cout << endl
             << "Pivot = " << pivot << ". L and R are pointing at beginning and end of array" << endl;
    }
    cout << endl;
}

int hoarePartition(int a[], int low, int high, int n)
{
    int pivot = a[low];
    int L = low + 1; // Start L after the pivot
    int R = high;

    cout << "Pivot element = " << pivot << " [" << low << "]" << endl
         << endl;

    cout << "Initial state:" << endl;
    printArray(a, n, L, R, true, pivot);

    while (true)
    {
        // Move L to the right to find element greater than pivot
        while (L <= high && a[L] <= pivot)
            L++;

        // Move R to the left to find element less than or equal to pivot
        while (R > low && a[R] > pivot)
            R--;

        cout << "L is at position " << L;
        if (L <= high)
            cout << " (value: " << a[L] << ")";
        cout << ", R is at position " << R << " (value: " << a[R] << ")" << endl;

        if (L < R)
        {
            printArray(a, n, L, R);
            cout << "L < R, swap " << a[L] << " & " << a[R] << endl;
            swap(a[L], a[R]);
            printArray(a, n, L, R);
            cout << "Continue searching..." << endl
                 << endl;
        }
        else
        {
            cout << "L >= R, partitioning complete." << endl;
            break;
        }
    }

    cout << "Swap pivot (" << pivot << ") with a[" << R << "] (" << a[R] << ")" << endl;
    swap(a[low], a[R]);

    cout << "After placing pivot in correct position:" << endl;
    printArray(a, n);

    cout << "Partition complete around pivot " << pivot << " at position " << R << endl;
    cout << string(50, '-') << endl
         << endl;

    return R;
}

void quickSortHoare(int a[], int low, int high, int n, int level = 0)
{
    if (low < high)
    {
        int p = hoarePartition(a, low, high, n);

        if (low < p - 1)
        {
            cout << "Recursively sorting left subarray [" << low << ", " << (p - 1) << "]" << endl
                 << endl;
            quickSortHoare(a, low, p - 1, n, level + 1);
        }

        if (p + 1 < high)
        {
            cout << "Recursively sorting right subarray [" << (p + 1) << ", " << high << "]" << endl
                 << endl;
            quickSortHoare(a, p + 1, high, n, level + 1);
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
         << "--- Quick Sort---" << endl
         << endl;

    quickSortHoare(a, 0, n - 1, n);

    cout << "Final Sorted Array:" << endl;
    printArray(a, n);

    delete[] a;
    return 0;
}
