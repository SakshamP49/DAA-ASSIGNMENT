#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Meeting;

typedef struct
{
    int heap[1000];
    int size;
} MinHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *h, int value)
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

int pop(MinHeap *h)
{
    int result = h->heap[0];

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

int compareMeetings(const void *a, const void *b)
{
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;

    if (x->start != y->start)
        return x->start - y->start;

    return x->end - y->end;
}

int main()
{
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    Meeting meetings[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter start and end time for meeting %d: ",
               i + 1);

        scanf("%d %d",
              &meetings[i].start,
              &meetings[i].end);
    }

    qsort(meetings, n,
          sizeof(Meeting),
          compareMeetings);

    MinHeap rooms;
    rooms.size = 0;

    int maximumRooms = 0;

    for (int i = 0; i < n; i++)
    {
        while (rooms.size > 0 &&
               rooms.heap[0] <= meetings[i].start)
        {
            pop(&rooms);
        }

        push(&rooms, meetings[i].end);

        if (rooms.size > maximumRooms)
            maximumRooms = rooms.size;
    }

    printf("Minimum number of meeting rooms = %d\n",
           maximumRooms);

    return 0;
}