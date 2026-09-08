#include <stdio.h>

void reverse(int arr[], int i, int j) {
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++; j--;
    }
}

// Swap adjacent blocks A (size m) and B (size n) starting at index 'start'
void blockSwap(int arr[], int start, int m, int n) {
    reverse(arr, start, start + m - 1);
    reverse(arr, start + m, start + m + n - 1);
    reverse(arr, start, start + m + n - 1);
}

// Binary search to find lower bound for partitioning
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

// In-place merge using reversal-based block swaps
void merge(int arr[], int left, int mid, int right) {
    if (left > mid || mid >= right) return;
    
    int L_len = mid - left + 1;
    int m_L_idx = left + L_len / 2;
    int m_L_val = arr[m_L_idx];
    
    int R_split = binarySearch(arr, mid + 1, right, m_L_val);
    
    int L2_len = mid - m_L_idx + 1;
    int R1_len = R_split - (mid + 1);
    
    if (L2_len > 0 && R1_len > 0) {
        blockSwap(arr, m_L_idx, L2_len, R1_len);
    }
    
    int new_mid = m_L_idx + R1_len;
    merge(arr, left, m_L_idx - 1, new_mid - 1);
    merge(arr, new_mid + 1, mid + R1_len, right);
}

// Merge Sort main function
void sortViaReversal(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sortViaReversal(arr, left, mid);
        sortViaReversal(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() { 
    int p[] = {1, 4, 3, 2, 5};
    int n = sizeof(p)/sizeof(p[0]);
    
    sortViaReversal(p, 0, n - 1);
    
    printf("Sorted permutation: ");
    for(int i = 0; i < n; i++) printf("%d ", p[i]);
    
    return 0;
}