#include <stdio.h>

typedef struct
{
    long long heap[1000];
    int size;
} MinHeap;

void swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *h, long long value)
{
    int i = h->size++;

    h->heap[i] = value;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (h->heap[parent] <= h->heap[i])
            break;

        swap(&h->heap[parent],
             &h->heap[i]);

        i = parent;
    }
}

long long pop(MinHeap *h)
{
    long long result = h->heap[0];

    h->size--;

    if (h->size > 0)
    {
        h->heap[0] =
            h->heap[h->size];

        int i = 0;

        while (1)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < h->size &&
                h->heap[left] < h->heap[smallest])
            {
                smallest = left;
            }

            if (right < h->size &&
                h->heap[right] < h->heap[smallest])
            {
                smallest = right;
            }

            if (smallest == i)
                break;

            swap(&h->heap[i],
                 &h->heap[smallest]);

            i = smallest;
        }
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    MinHeap heap;
    heap.size = 0;

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++)
    {
        long long length;
        scanf("%lld", &length);

        push(&heap, length);
    }

    long long totalCost = 0;

    while (heap.size > 1)
    {
        long long a = pop(&heap);
        long long b = pop(&heap);

        long long sum = a + b;

        totalCost += sum;

        push(&heap, sum);
    }

    printf("Minimum total cost = %lld\n",
           totalCost);

    return 0;
}