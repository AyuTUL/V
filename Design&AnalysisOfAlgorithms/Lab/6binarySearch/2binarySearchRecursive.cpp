// Lab 6.2: WAP to implement binary search using recursive method.
//table baki
#include <iostream>
using namespace std;

int binarySearchRecursive(int *a, int low, int high, int key)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (a[mid] == key)
        return mid;
    else if (a[mid] < key)
        return binarySearchRecursive(a, mid + 1, high, key);
    else
        return binarySearchRecursive(a, low, mid - 1, key);
}

int main()
{
    int *a, n, key, index;

    cout << "--- Binary Search using Recursive Method ---" << endl;
    cout << "Enter array size : ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " sorted elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "Enter element to be searched : ";
    cin >> key;

    index = binarySearchRecursive(a, 0, n - 1, key);

    if (index == -1)
        cout << "\nElement not found in array.";
    else
        cout << "\nElement found at position " << index + 1 << ".";

    delete[] a;
    return 0;
}