#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSortParallel(vector<int> &arr, int low, int high) {
    if (low >= high) {
        return;
    }
    int mid = (low + high) / 2 ;
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section 
        {
            mergeSortParallel(arr, low, mid);  // left half
        }
        
        #pragma omp section 
        {
            mergeSortParallel(arr, mid + 1, high); // right half
        }
    }
    merge(arr, low, mid, high);  // merging sorted halves
}

int main() {

    vector<int> arr = {9, 4, 7, 6, 3, 1, 5, 2, 8}  ;
    int n = arr.size();

    cout << "Before Sorting Array: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "  ;
    }
    cout << endl;

    double start, end;

    start = omp_get_wtime();
    mergeSortParallel(arr, 0, n - 1);
    end = omp_get_wtime();

    cout << "Time taken: " << end - start << endl;

    cout << "After Sorting Array: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "  ;
    }
    cout << endl;
    return 0 ;
}