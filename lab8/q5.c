#include <stdio.h>
#include <stdlib.h>

int maxSumIncreasingSubsequence(int arr[], int n)
{
    int *dp = malloc(n * sizeof(int));

    if (dp == NULL)
        return -1;

    int maximum = 0;

    for (int i = 0; i < n; i++)
        dp[i] = arr[i];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i])
            {
                int current = dp[j] + arr[i];

                if (current > dp[i])
                    dp[i] = current;
            }
        }

        if (dp[i] > maximum)
            maximum = dp[i];
    }

    if (n > 0 && dp[0] > maximum)
        maximum = dp[0];

    free(dp);

    return maximum;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter positive integers:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int answer =
        maxSumIncreasingSubsequence(arr, n);

    printf("Maximum sum = %d\n", answer);

    free(arr);

    return 0;
}