// Lab 4: WAP to implement sequential(linear) search.
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void printBorder()
{
    cout << "+-----+----------------+----------+" << endl;
}

void printTableHeader(int key)
{
    printBorder();
    cout << "|  i  |  A[i] == key   |  Return  |" << endl;
    printBorder();
}

void printTableRow(int i, int value, int key, bool found, int returnValue)
{
    cout << "|  " << i << "  |  " << setw(4) << right << value << " == " << setw(4) << left << key
         << "  |   ";
    if (found)
        cout << setw(7) << left << returnValue << "|" << endl;
    else
        cout << " No    |" << endl;
}

void printTableFooter()
{
    printBorder();
}

int linearSearch(int *a, int n, int key)
{
    cout << endl;
    printTableHeader(key);

    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            printTableRow(i, a[i], key, true, i);
            printTableFooter();
            cout << endl
                 << "Element " << key << " found at index " << i;
            return i;
        }
        printTableRow(i, a[i], key, false, -1);
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
    cout << endl
         << "---Linear Search---" << endl;
    linearSearch(a, n, key);

    delete[] a;
    return 0;
}