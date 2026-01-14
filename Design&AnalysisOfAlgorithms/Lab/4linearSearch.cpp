// Lab 4: WAP to implement sequential(linear) search.
#include <iostream>
#include <stdlib.h>
using namespace std;
int linearSearch(int *a, int n, int key)
{
    for (int i = 0; i < n; i++)
        if (a[i] == key)
            return i;
    return -1;
}
int main()
{
    int *a, n, key, index;
    cout << "---Linear Search---" << endl;
    cout << "Enter array size : ";
    cin >> n;
    a = new int[n];
    cout << "Enter elements " << n << " : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Enter element to be searched : ";
    cin >> key;
    index = linearSearch(a, n, key);
    if (index == -1)
        cout << endl
             << "Element not found in array.";
    else
        cout << endl
             << "Element found at position " << index + 1 << ".";
    delete[] a;
    return 0;
}