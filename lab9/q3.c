#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int distance;
    int fuel;
} Station;

typedef struct
{
    int heap[1000];
    int size;
} MaxHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap *h, int value)
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

int pop(MaxHeap *h)
{
    int result = h->heap[0];

    h->size--;

    h->heap[0] = h->heap[h->size];

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

    return result;
}

int compareStations(const void *a, const void *b)
{
    Station *x = (Station *)a;
    Station *y = (Station *)b;

    return x->distance - y->distance;
}

int main()
{
    int n;
    int D, F;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    Station stations[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter distance and fuel for station %d: ",
               i + 1);

        scanf("%d %d",
              &stations[i].distance,
              &stations[i].fuel);
    }

    qsort(stations, n,
          sizeof(Station),
          compareStations);

    MaxHeap heap;
    heap.size = 0;

    int currentPosition = 0;
    int fuel = F;
    int stops = 0;

    for (int i = 0; i < n; i++)
    {
        if (stations[i].distance > D)
            break;

        int distanceNeeded =
            stations[i].distance - currentPosition;

        while (fuel < distanceNeeded)
        {
            if (heap.size == 0)
            {
                printf("Cannot reach the target.\n");
                return 0;
            }

            fuel += pop(&heap);
            stops++;
        }

        fuel -= distanceNeeded;
        currentPosition = stations[i].distance;

        push(&heap, stations[i].fuel);
    }

    int distanceNeeded = D - currentPosition;

    while (fuel < distanceNeeded)
    {
        if (heap.size == 0)
        {
            printf("Cannot reach the target.\n");
            return 0;
        }

        fuel += pop(&heap);
        stops++;
    }

    printf("Minimum number of refuelling stops = %d\n",
           stops);

    return 0;
}