// Lab 6.1: WAP to implement binary search using iterative method.
//table baki
#include <iostream>
using namespace std;

int binarySearch(int *a, int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (a[mid] == key)
            return mid;
        else if (a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main()
{
    int *a, n, key, index;

    cout << "--- Binary Search using Iterative Method ---" << endl;
    cout << "Enter array size : ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " sorted elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "Enter element to be searched : ";
    cin >> key;

    index = binarySearch(a, n, key);

    if (index == -1)
        cout << "Element not found in array.";
    else
        cout << "Element found at position " << index + 1 << ".";

    delete[] a;
    return 0;
}