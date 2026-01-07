// Lab 1.3: Define sorting concept. WAP to sort array using bubble sort and analyze it.
#include <iostream>
using namespace std;

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

void bubble(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        cout << "\n========================\n";
        cout << "Pass " << i + 1 << " starts\n";
        cout << "Array at start: ";
        printArray(a, n);

        for (int j = 0; j < n - i - 1; j++)
        {
            cout << "Comparing " << a[j] << " and " << a[j + 1];

            if (a[j] > a[j + 1])
            {
                cout << " -> Swap\n";
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                cout << "Array after swap: ";
                printArray(a, n);
            }
            else
            {
                cout << " -> No swap\n";
            }
        }

        cout << "Array at end of Pass " << i + 1 << ": ";
        printArray(a, n);
    }
}

int main()
{
    int *a, n;
    cout << "Enter array size: ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "\nBefore sorting:\n";
    printArray(a, n);

    cout << "\nBubble Sort Detailed Steps:\n";
    bubble(a, n);

    cout << "\nFinal sorted array:\n";
    printArray(a, n);

    delete[] a;
    return 0;
}
