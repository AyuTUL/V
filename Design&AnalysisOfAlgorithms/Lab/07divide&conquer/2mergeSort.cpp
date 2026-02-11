// Merge Sort with Proper Divide & Merge Display
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Info
{
    int l, h;
};

vector<vector<Info>> divideLvls, mergeLvls;

// Print Levels
void printLevel(int a[], vector<vector<Info>> &levels, int lvl, string title)
{
    if (lvl >= levels.size())
        return;

    cout << title << " Level " << lvl << " :" << endl;

    for (int pass = 0; pass < 3; pass++)
    {
        for (int i = 0; i < levels[lvl].size(); i++)
        {
            auto &x = levels[lvl][i];

            if (pass == 1)
            {
                cout << "|";
                for (int j = x.l; j <= x.h; j++)
                    cout << setw(3) << a[j] << " |";
            }
            else
            {
                cout << "+";
                for (int j = x.l; j <= x.h; j++)
                    cout << "----+";
            }

            if (i < levels[lvl].size() - 1)
                cout << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

// Merge Function
void merge(int a[], int low, int mid, int high, int lvl)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    delete[] L;
    delete[] R;

    int mergeWave = (divideLvls.size() - 1) - lvl - 1;

    if (mergeWave < 0)
        mergeWave = 0;

    if (mergeWave >= mergeLvls.size())
        mergeLvls.resize(mergeWave + 1);

    mergeLvls[mergeWave].push_back({low, high});
}

void mergeSort(int a[], int low, int high, int lvl = 0)
{
    // Resize level storage if needed
    if (lvl >= divideLvls.size())
        divideLvls.resize(lvl + 1);

    // Store current subarray in divide phase
    divideLvls[lvl].push_back({low, high});

    // Base condition
    if (low == high)
        return;

    int mid = (low + high) / 2;

    // Go deeper for both halves
    mergeSort(a, low, mid, lvl + 1);
    mergeSort(a, mid + 1, high, lvl + 1);

    merge(a, low, mid, high, lvl);
}

int main()
{
    int n;
    cout << "--- Merge Sort using Divide & Conquer ---" << endl;

    cout << "Enter array size : ";
    cin >> n;

    int *a = new int[n];
    int *original = new int[n]; // Copy of original array

    cout << "Enter " << n << " elements : ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        original[i] = a[i]; // Save original values
    }

    cout << endl;

    mergeSort(a, 0, n - 1);

    cout << "======= DIVIDE PHASE =======" << endl
         << endl;
    for (int i = 0; i < divideLvls.size(); i++)
        printLevel(original, divideLvls, i, "Divide");

    cout << "======= MERGE PHASE =======" << endl
         << endl;
    for (int i = 0; i < mergeLvls.size(); i++)
        printLevel(a, mergeLvls, i, "Merge");

    cout << "Final Sorted Array :" << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    delete[] a;
    delete[] original;
    return 0;
}
