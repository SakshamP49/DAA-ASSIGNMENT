#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int has_duplicates(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            return 1; // Duplicate found
        }
    }
    return 0; // Unique
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (has_duplicates(arr, n)) {
        printf("Duplicates exist.\n");
    } else {
        printf("All elements are unique.\n");
    }
    return 0;
}