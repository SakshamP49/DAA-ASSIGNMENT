#include <stdio.h>

typedef struct
{
    long long heap[1000];
    int size;
} MaxHeap;

void swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap *h, long long value)
{
    int i = h->size++;

    h->heap[i] = value;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (h->heap[parent] >= h->heap[i])
            break;

        swap(&h->heap[parent],
             &h->heap[i]);

        i = parent;
    }
}

long long pop(MaxHeap *h)
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
            int largest = i;

            if (left < h->size &&
                h->heap[left] > h->heap[largest])
            {
                largest = left;
            }

            if (right < h->size &&
                h->heap[right] > h->heap[largest])
            {
                largest = right;
            }

            if (largest == i)
                break;

            swap(&h->heap[i],
                 &h->heap[largest]);

            i = largest;
        }
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    MaxHeap heap;
    heap.size = 0;

    long long minimum = 1000000000000000000LL;

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
    {
        long long x;
        scanf("%lld", &x);

        if (x % 2 == 1)
            x *= 2;

        if (x < minimum)
            minimum = x;

        push(&heap, x);
    }

    long long answer =
        heap.heap[0] - minimum;

    while (heap.size > 0)
    {
        long long maximum = heap.heap[0];

        if (maximum % 2 == 1)
            break;

        pop(&heap);

        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        push(&heap, maximum);

        long long currentDeviation =
            heap.heap[0] - minimum;

        if (currentDeviation < answer)
            answer = currentDeviation;
    }

    printf("Minimum deviation = %lld\n",
           answer);

    return 0;
}