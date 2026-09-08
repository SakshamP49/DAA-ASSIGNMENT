#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Helper for sorting (used in Mode, Median, Remove Duplicates)
int compare(const void *a, const void *b)
 { return (*(int *)a - *(int *)b); }

// (i) Max
int findMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// (ii) First and Second Max
void findFirstSecondMax(int arr[], int n, int *max1, int *max2)
{
    *max1 = *max2 = -2147483648;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > *max1)
        {
            *max2 = *max1;
            *max1 = arr[i];
        }
        else if (arr[i] > *max2 && arr[i] != *max1)
        {
            *max2 = arr[i];
        }
    }
}

// (iii) Mean
double findMean(int arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum / n;
}

// (iv) Median (using sort for simplicity)
double findMedian(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    if (n % 2 != 0)
        return arr[n / 2];
    return (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
}

// (v) Standard Deviation
double findStdDev(int arr[], int n)
{
    double mean = findMean(arr, n);
    double varSum = 0;
    for (int i = 0; i < n; i++)
        varSum += pow(arr[i] - mean, 2);
    return sqrt(varSum / n);
}

// (vi) Mode
int findMode(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    int max_count = 1, res = arr[0], curr_count = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
            curr_count++;
        else
            curr_count = 1;
        if (curr_count > max_count)
        {
            max_count = curr_count;
            res = arr[i - 1];
        }
    }
    return res;
}

// (vii) Remove duplicates (returns new size)
int removeDuplicates(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    int j = 0;
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            arr[j++] = arr[i];
    arr[j++] = arr[n - 1];
    return j;
}

// (viii) Reverse
void reverseArray(int arr[], int n)
{
    for (int i = 0; i < n / 2; i++)
        swap(&arr[i], &arr[n - i - 1]);
}

// (ix) Partition ( < pivot after >= pivot )
void customPartition(int arr[], int n, int pivot)
{
    int i = 0, j = n - 1;
    while (i <= j)
    {
        while (i < n && arr[i] >= pivot)
            i++;
        while (j >= 0 && arr[j] < pivot)
            j--;
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
}

int main()
{
    int arr[] = {12, 3, 5, 7, 19, 3, 5, 21};
    int n = sizeof(arr) / sizeof(arr[0]);
    // Validate routines here by calling functions...
    return 0;
}