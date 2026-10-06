#include <stdio.h>
#include <stdlib.h>

int LIS(int arr[], int n)
{
    int *dp = malloc(n * sizeof(int));

    if (dp == NULL)
        return -1;

    int maximum = 1;

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i])
            {
                if (dp[j] + 1 > dp[i])
                    dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > maximum)
            maximum = dp[i];
    }

    free(dp);

    return maximum;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int answer = LIS(arr, n);

    printf("Length of LIS = %d\n", answer);

    free(arr);

    return 0;
}