#include <stdio.h>

int find_partition_point(int arr[], int n) {
    int low = 0, high = n - 1;
    int partition = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == 1) {
            partition = mid;
            high = mid - 1; // look for earlier 1
        } else {
            low = mid + 1; // 0 found, look in right half
        }
    }
    return partition;
}

int main() {
    int arr[] = {0, 0, 0, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int point = find_partition_point(arr, n);
    printf("Partition point (first occurrence of 1): index %d\n", point);
    return 0;
}