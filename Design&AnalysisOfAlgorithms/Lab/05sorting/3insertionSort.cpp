// Lab 5.3 : Implement insertion sort algorithm.
//wrong
#include <iostream>
#include <iomanip>
using namespace std;

void printBorder()
{
    cout << "+-----+--------------+-----------------+" << endl;
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
    cout << "|  j  |  A[j] > key  |  A[j+1] = A[j]  |" << endl;
    printBorder();
}

void printTableRow(int j, int aj, int key)
{
    cout << "|  " << setw(3) << left << j << "|   "
         << setw(3) << right << aj << " > "
         << setw(5) << left << key
         << "|    A[" << j + 1 << "] = "
         << setw(3) << left << aj << "   |" << endl;
}

void printMinusOneRow()
{
    cout << "| -1  |      -       |        -        |" << endl;
}

void printTableFooter()
{
    printBorder();
}

void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        cout << endl
             << "Pass " << i
             << " : [ i = " << i
             << ", key = A[" << i << "] = " << key
             << ", j = " << j << " to 0 ]" << endl << endl;

        printTableHeader();

        while (j >= 0 && a[j] > key)
        {
            printTableRow(j, a[j], key);
            a[j + 1] = a[j];
            j--;
        }

        printMinusOneRow();
        if(j<0)
        printTableFooter();

        cout << endl
             << "j = " << j << endl;
        cout << "A[" << j + 1 << "] = " << key << endl;

        a[j + 1] = key;

        cout << endl
             << "After Pass " << i  << " :";
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
         << "--- Insertion Sort Algorithm ---" << endl;

    insertionSort(a, n);

    delete[] a;
    return 0;
}
