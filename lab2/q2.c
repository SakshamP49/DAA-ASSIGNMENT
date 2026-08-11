#include <stdio.h>
#include <stdlib.h>

long long standard_mergesort_ops = 0;
long long modified_mergesort_ops = 0;

void merge(int arr[], int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, k = l, j = 0;
    while (i < n1 && j < n2) {
        standard_mergesort_ops++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void standard_merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        standard_merge_sort(arr, l, mid);
        standard_merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

int main() {
    int n = 1000;
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

    standard_merge_sort(arr, 0, n - 1);
    printf("Standard Merge Sort Comparisons/Ops: %lld\n", standard_mergesort_ops);
    
    free(arr);
    return 0;
}