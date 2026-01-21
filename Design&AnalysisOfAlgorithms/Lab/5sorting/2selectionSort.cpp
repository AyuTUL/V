// Lab 5.2 : Selection Sort with ASCII Table Output
//after table text check
#include <iostream>
#include <iomanip>
using namespace std;

void printArray(int *a, int n)
{
    cout << "  ";
    for (int i = 0; i < n; i++)
        cout << setw(5) << a[i];
}

void printIndex(int n)
{
    cout << "  ";
    for (int i = 1; i <= n; i++)
        cout << setw(3) << i << " ";
    cout << endl;
}

void printTableHeader()
{
    cout << "+-----+-----------------+---------+" << endl
         << "|  j  |  A[j] < A[min]  |  min=j  |" << endl
         << "+-----+-----------------+---------+" << endl;
}

void printTableRow(int j, int aj, int amin, bool update)
{
    cout << "|  " << j << "  |   " << setw(3) << right << aj << " < " << setw(3) << left << amin << "     |" << (update ? "   Yes  " : "   No   ") << " |" << endl;
}

void printTableFooter()
{
    cout << "+-----+-----------------+---------+" << endl;
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

            if (a[j] < a[minIndex])
            {
                minIndex = j;
                update = true;
            }

            printTableRow(j + 1, a[j], a[minIndex], update);
        }

        printTableFooter();

        if (minIndex != i)
        {
            cout << "\nmin != i, so swap A[" << i + 1
                 << "] and A[" << minIndex + 1 << "]\n";

            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;

            cout << endl
                 << "After Pass " << i + 1 << " :";
            printArray(a, n);
            cout << endl<<"----------------------------------" << endl;
        }
        else
        {
            cout << "\nmin == i, no swap required\n";
        }

    }

    cout << "Final Sorted Array\n";
    printIndex(n);
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

    cout << "\n--- Selection Sort Algorithm ---\n";
    selectionSort(a, n);

    delete[] a;
    return 0;
}
