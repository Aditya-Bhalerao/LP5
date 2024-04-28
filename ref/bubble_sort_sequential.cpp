#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

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

int main() {
    vector<int> arr = {5, 1, 4, 2, 8};
    //vector<int> arr(1000); // Create a vector of size 1000
    //for (int i = 0; i < 1000; i++) {
    //arr[i] = rand() % 1000;
    //}

    cout << "Original array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    

    // Time the sort function
    auto start = high_resolution_clock::now();
    bubble_sort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    //cout << "Array sorted";	
    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    cout << "Time taken by bubble sort: " << duration.count() << " microseconds" << endl;

    return 0;
}
