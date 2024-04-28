#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i];
        if (i < arr.size() - 1)
            cout << " ";
    }
    cout << endl;
}

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void parallel_bubble_sort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    omp_set_num_threads(2);  
    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = false;
        #pragma omp parallel for shared(arr) reduction(||:swapped)
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}

int main() {
    vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    cout << "Original array: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    double start, end;

    // Measure performance of sequential bubble sort
    start = omp_get_wtime();
    bubble_sort(arr);
    end = omp_get_wtime();
    cout << "Sequential bubble sort time: " << end - start << endl;

    // Reset array for parallel version
    arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};

    // Measure performance of parallel bubble sort using odd-even transposition
    start = omp_get_wtime();
    parallel_bubble_sort(arr);
    end = omp_get_wtime();
    cout << "Parallel bubble sort time: " << end - start << endl;
    printArray(arr);
    return 0;
}
