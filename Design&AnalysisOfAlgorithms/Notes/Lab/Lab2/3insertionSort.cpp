// Lab 2.3: WAP to sort array using insertion sort.
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
        cout << "Iteration " << i + 1 << " :"<<endl;
        printArray(a, n);

        for (int j = 0; j < n - i - 1; j++)
        {
            cout << "Comparing " << a[j] << " and " << a[j + 1];

            if (a[j] > a[j + 1])
            {
                cout << " -> Swap"<<endl;
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                printArray(a, n);
            }
            else
            {
                cout << " -> No swap"<<endl;
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

    cout << endl<< "Before sorting :"<<endl;
    printArray(a, n);

    cout << endl<<"Bubble Sort :"<<endl;
    bubble(a, n);

    cout << endl<<"Final sorted array :"<<endl;
    printArray(a, n);

    delete[] a;
    return 0;
}
