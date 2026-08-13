#include <stdio.h>

typedef struct
{
    int min;
    int max;
} Result;

Result findMinMax(int arr[], int low, int high)
{
    Result result, left, right;

    // Only one element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];

        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    int mid = (low + high) / 2;

    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    Result result = findMinMax(arr, 0, n - 1);

    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);

    return 0;
}