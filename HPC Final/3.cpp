#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to find the minimum value using parallel reduction
int parallelMin(const vector<int>& arr) {
    int minVal = arr[0];
    #pragma omp parallel for reduction(min:minVal)
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// Function to find the maximum value using parallel reduction
int parallelMax(const vector<int>& arr) {
    int maxVal = arr[0];
    #pragma omp parallel for reduction(max:maxVal)
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Function to compute the sum using parallel reduction
int parallelSum(const vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (size_t i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    return sum;
}

// Function to compute the average using parallel reduction
double parallelAverage(const vector<int>& arr) {
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    cout << "Minimum: " << parallelMin(arr) << endl;
    cout << "Maximum: " << parallelMax(arr) << endl;
    cout << "Sum: " << parallelSum(arr) << endl;
    cout << "Average: " << parallelAverage(arr) << endl;

    return 0;
}
