#include "../include/sort.h"
#include "../include/swap.h"

// Partition function to rearrange the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Choose the last element as the pivot
    int i = (low - 1);  // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++;
            int_swap(&arr[i], &arr[j]);
        }
    }

    // Swap the pivot element with the element at (i + 1), placing the pivot in its correct position
    int_swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Recursive function to perform Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Find the pivot index such that elements smaller than the pivot are on the left, and larger on the right
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the subarrays on both sides of the pivot
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}


