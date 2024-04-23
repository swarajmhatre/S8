#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

// Sequential bubble sort
void sequentialBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel bubble sort
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Sequential merge sort
void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void sequentialMergeSortHelper(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        sequentialMergeSortHelper(arr, l, m);
        sequentialMergeSortHelper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void sequentialMergeSort(vector<int> &arr)
{
    sequentialMergeSortHelper(arr, 0, arr.size() - 1);
}

// Parallel merge sort
void parallelMergeSortHelper(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSortHelper(arr, l, m);
#pragma omp section
            parallelMergeSortHelper(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

void parallelMergeSort(vector<int> &arr)
{
    parallelMergeSortHelper(arr, 0, arr.size() - 1);
}

// Function to generate random array
vector<int> generateRandomArray(int size)
{
    vector<int> arr(size);
    cout << "Enter " << size << " integers separated by space:\n";
    for (int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }
    return arr;
}

int main()
{
    srand(time(nullptr)); // Seed for random number generation

    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr = generateRandomArray(size);
    vector<int> arrCopy = arr; // Make a copy of the original array

    // Sort the array using Sequential Bubble Sort
    clock_t start = clock();
    sequentialBubbleSort(arr);
    clock_t end = clock();
    cout << "Sorted array: ";
    for (int i : arr)
        cout << i << " ";
    cout << endl;
    cout << "Time (Sequential Bubble Sort): " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    // Sort the array using Parallel Bubble Sort
    arr = arrCopy; // Reset array to original state
    start = clock();
    parallelBubbleSort(arr);
    end = clock();
    cout << "Time(Parallel Bubble Sort): " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    // Sort the array using Sequential Merge Sort
    arr = arrCopy; // Reset array to original state
    start = clock();
    sequentialMergeSort(arr);
    end = clock();
    cout << "Time(Sequential Merge Sort): " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    // Sort the array using Parallel Merge Sort
    arr = arrCopy; // Reset array to original state
    start = clock();
    parallelMergeSort(arr);
    end = clock();
    cout << "Time(Parallel Merge Sort): " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    return 0;
}
