// Lab 6.1: WAP to implement binary search using iterative method with sorting
#include <iostream>
#include <iomanip>
using namespace std;

void sortArray(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

void printArray(int *a, int n)
{
    cout << endl
         << "Sorted Array :" << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

void printBorder()
{
    cout << "+--------+-------+--------+---------------+-------+-----------------+----------------------------+" << endl;
}

void printTableHeader(int key)
{
    printBorder();
    cout << "|  Call  |  Low  |  High  |  Low == High  |  Mid  |  A[mid] vs Key  |  Remarks                   |" << endl;
    printBorder();
}

void printTableRow(int call, int low, int high, bool same,
                   int mid, int midVal, int key, string remark)
{
    cout << "|  " << setw(6) << left << call
         << "|  " << setw(5) << left << low
         << "|  " << setw(6) << left << high
         << "|      " << setw(9) << left << (same ? "Yes" : "No ")
         << "|  " << setw(5) << left << mid
         << "|    " << setw(3) << right << midVal
         << (midVal < key ? " < " : midVal > key ? " > "
                                                 : " = ")
         << setw(7) << left << key
         << "|  " << setw(26) << left << remark << "|" << endl;
}

void printTableFooter()
{
    printBorder();
}

int binarySearch(int *a, int n, int key)
{
    int low = 0, high = n - 1;
    int call = 1;

    cout << endl;
    printTableHeader(key);

    while (low <= high)
    {
        int mid = (low + high) / 2;
        bool same = (low == high);

        if (a[mid] == key)
        {
            printTableRow(call, low, high, same, mid, a[mid], key,
                          "A[mid] == key, Found");
            printTableFooter();
            cout << endl
                 << "Element " << key << " found at index " << mid;
            return mid;
        }
        else if (a[mid] < key)
        {
            printTableRow(call, low, high, same, mid, a[mid], key,
                          "Search right half");
            low = mid + 1;
        }
        else
        {
            printTableRow(call, low, high, same, mid, a[mid], key,
                          "Search left half");
            high = mid - 1;
        }
        call++;
    }

    printTableFooter();
    cout << endl
         << "Element " << key << " not found in array.";
    return -1;
}

int main()
{
    int *a, n, key;

    cout << "Enter array size : ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "Enter element to be searched : ";
    cin >> key;

    sortArray(a, n);
    printArray(a, n);

    cout << endl
         << "---Binary Search using Iterative Method---" << endl;

    binarySearch(a, n, key);

    delete[] a;
    return 0;
}