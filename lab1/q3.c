#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long bubble_sort_optimized(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1] ) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    return comparisons;
}

long long bubble_sort_standard(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

int main() {
    int n = 1000;
    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc(n * sizeof(int));
    
    for(int i = 0; i < n; i++) {
        arr1[i] = rand() % 10000;
        arr2[i] = arr1[i];
    }
    
    printf("Optimized Bubble Sort Comparisons: %lld\n", bubble_sort_optimized(arr1, n));
    printf("Standard Bubble Sort Comparisons: %lld\n", bubble_sort_standard(arr2, n));
    
    free(arr1);
    free(arr2);
    return 0;
}