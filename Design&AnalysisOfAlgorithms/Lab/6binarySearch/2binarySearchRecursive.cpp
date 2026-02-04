// Lab 6.2: WAP to implement binary search using recursive method with table
#include <iostream>
#include <iomanip>
using namespace std;

void printBorder()
{
    cout << "+--------+-------+--------+-------+-----------------+----------+" << endl;
}

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

void printTableHeader(int key)
{
    printBorder();
    cout << "|  Call  |  Low  |  High  |  Mid  |  A[mid] == Key  |  Return  |" << endl;
    printBorder();
}

void printTableRow(int call, int low, int high, int mid,
                   int midVal, int key, int ret)
{
    cout << "|  " << setw(6) << left << call
         << "|  " << setw(5) << left << low
         << "|  " << setw(6) << left << high
         << "|  " << setw(5) << left << mid
         << "|    " << setw(3) << right << midVal << " == "
         << setw(3) << left << key
         << "   |     ";

    if (ret != -2)
        cout << setw(5) << left << ret << "|";
    else
        cout << "-    |";

    cout << endl;
}

void printTableFooter()
{
    printBorder();
}

int binarySearchRecursive(int *a, int low, int high, int key, int &call)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (a[mid] == key)
    {
        printTableRow(call++, low, high, mid, a[mid], key, mid);
        return mid;
    }

    printTableRow(call++, low, high, mid, a[mid], key, -2);

    if (a[mid] < key)
        return binarySearchRecursive(a, mid + 1, high, key, call);
    else
        return binarySearchRecursive(a, low, mid - 1, key, call);
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
         << "--- Binary Search using Recursive Method ---" << endl;

    cout << endl;
    printTableHeader(key);

    int call = 1;
    int index = binarySearchRecursive(a, 0, n - 1, key, call);

    printTableFooter();

    if (index == -1)
        cout << endl
             << "Element not found in array.";
    else
        cout << endl
             << "Element found at position " << index + 1 << ".";

    delete[] a;
    return 0;
}