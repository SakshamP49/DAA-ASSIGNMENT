#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start;
    int end;
};

int compare(const void *a, const void *b) {
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b;

    return i1->start - i2->start;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval arr[n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
        scanf("%d %d", &arr[i].start, &arr[i].end);

    qsort(arr, n, sizeof(struct Interval), compare);

    printf("Merged intervals:\n");

    int currentStart = arr[0].start;
    int currentEnd = arr[0].end;

    for (int i = 1; i < n; i++) {

        if (arr[i].start <= currentEnd) {
            // Intervals overlap
            if (arr[i].end > currentEnd)
                currentEnd = arr[i].end;
        }
        else {
            // No overlap
            printf("(%d, %d) ",
                   currentStart, currentEnd);

            currentStart = arr[i].start;
            currentEnd = arr[i].end;
        }
    }

    // Print the last interval
    printf("(%d, %d)\n",
           currentStart, currentEnd);

    return 0;
}