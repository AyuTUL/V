// Lab 5.1: Implement bubble sort algorithm.
#include <iostream>
#include <iomanip>
using namespace std;

int borderWidth = 0;

void printBorder()
{
    cout << "+-----+-----------------+--------+";
    for (int i = 0; i < borderWidth; i++)
        cout << "-";
    cout << "+" << endl;
}

void printArray(int *a, int n)
{
    cout << "  ";
    for (int i = 0; i < n; i++)
        cout << setw(5) << a[i];
}

void printTableHeader(int n)
{
    printBorder();
    cout << "|  j  |  A[j] > A[j+1]  |  Swap  |" << setw(borderWidth) << left << "  Array" << "|" << endl
         << "+-----+-----------------+--------+";
    for (int i = 0; i < borderWidth; i++)
        cout << "-";
    cout << "+" << endl;
}

void printTableRow(int j, int val1, int val2, bool swapped, int *a, int n)
{
    cout << "|  " << j << "  |   " << setw(3) << right << val1 << " > " << setw(3) << left << val2 << "     |" << (swapped ? "   Yes  " : "   No   ") << "|";
    printArray(a, n);
    cout << "|" << endl;
}

void printTableFooter(int n)
{
    printBorder();
}

void bubble(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        cout << endl
             << "Pass " << i + 1 << " : [ i = " << i << ", j = 0 to " << n - i - 2 << "]" << endl
             << endl;

        printTableHeader(n);

        for (int j = 0; j < n - i - 1; j++)
        {
            int val1 = a[j];
            int val2 = a[j + 1];
            bool swapped = false;

            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = true;
            }

            printTableRow(j, val1, val2, swapped, a, n);
        }

        printTableFooter(n);

        cout << endl
             << "After Pass " << i + 1 << " :";
        printArray(a, n);
        cout << endl
             << "--------------------------------------------" << endl;
    }

    cout << endl
         << "Final sorted array :";
    printArray(a, n);
    cout << endl;
}

int main()
{
    int *a, n;
    cout << "Enter array size : ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << endl
         << "---Bubble Sort Algorithm---" << endl;
    borderWidth = n * 5 + 2;
    bubble(a, n);

    delete[] a;
    return 0;
}
