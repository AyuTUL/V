// Lab 5.2 : Implement selection sort algorithm.
#include <iostream>
#include <iomanip>
using namespace std;

void printBorder()
{
    cout << "+-----+-----------------+--------------+" << endl;
}

void printArray(int *a, int n)
{
    cout << "  ";
    for (int i = 0; i < n; i++)
        cout << setw(5) << a[i];
}

void printTableHeader()
{
    printBorder();
    cout << "|  j  |  A[j] < A[min]  |   min = j    |" << endl;
    printBorder();
}

void printTableRow(int j, int aj, int amin, bool update, int minIdx)
{
    cout << "|  " << j << "  |   " << setw(3) << right << aj << " < " << setw(3) << left << amin << "     |";
    if (update)
        cout << "   min = " << setw(4) << left << minIdx << " |" << endl;
    else
        cout << "      No      |" << endl;
}

void printTableFooter()
{
    printBorder();
}

void selectionSort(int *a, int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        cout << endl
             << "Pass " << i + 1 << " : [ i = " << i
             << ", min = " << i << ", j = " << i + 1 << " to " << n - 1 << " ]"
             << endl
             << endl;

        printTableHeader();

        for (int j = i + 1; j < n; j++)
        {
            bool update = false;
            int currentMin = a[minIndex];
            if (a[j] < a[minIndex])
            {
                minIndex = j;
                update = true;
            }

            printTableRow(j, a[j], currentMin, update, minIndex);
        }

        printTableFooter();

        if (minIndex != i)
        {
            cout << endl
                 << "min != i, swap(A[" << i
                 << "],A[" << minIndex << "])" << endl;

            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;
        }
        else
        {
            cout << endl
                 << "min == i, no swap " << endl;
        }

        cout << endl
             << "After Pass " << i + 1 << " :";
        printArray(a, n);
        cout << endl
             << "--------------------------------------------" << endl;
    }

    cout << endl
         << "Final Sorted Array :";

    printArray(a, n);
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
         << "--- Selection Sort Algorithm ---" << endl;
    selectionSort(a, n);

    delete[] a;
    return 0;
}
