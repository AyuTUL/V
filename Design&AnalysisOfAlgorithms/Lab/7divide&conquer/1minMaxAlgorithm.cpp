// Lab 7.1: WAP to implement Min-Max algorithm using divide & conquer.
//table baki
#include <iostream>
using namespace std;

struct MinMax
{
    int min;
    int max;
};

MinMax findMinMax(int a[], int low, int high)
{
    MinMax result, left, right;

    // Case 1: Only one element
    if (low == high)
    {
        result.min = a[low];
        result.max = a[low];
        return result;
    }

    // Case 2: Two elements
    if (high == low + 1)
    {
        if (a[low] < a[high])
        {
            result.min = a[low];
            result.max = a[high];
        }
        else
        {
            result.min = a[high];
            result.max = a[low];
        }
        return result;
    }

    // Case 3: More than two elements
    int mid = (low + high) / 2;

    left = findMinMax(a, low, mid);
    right = findMinMax(a, mid + 1, high);

    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main()
{
    int n;
    cout << "--- Min-Max Algorithm using Divide and Conquer ---" << endl;

    cout << "Enter array size : ";
    cin >> n;

    int *a = new int[n];

    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    MinMax ans = findMinMax(a, 0, n - 1);

    cout << "\nMinimum element : " << ans.min;
    cout << "\nMaximum element : " << ans.max;

    delete[] a;
    return 0;
}
