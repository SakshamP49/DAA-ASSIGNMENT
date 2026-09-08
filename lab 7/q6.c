#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;
} Event;

int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    // Earlier year comes first
    if (e1->year != e2->year)
        return e1->year - e2->year;

    // Death (-1) must come before birth (+1)
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    Event events[2 * n];

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Enter birth and death year of scientist %d: ",
               i + 1);

        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == -1)
        {
            alive--;
        }
        else
        {
            alive++;

            if (alive > maximum)
            {
                maximum = alive;
                bestYear = events[i].year;
            }
        }
    }

    printf("\nMaximum number of scientists alive = %d\n",
           maximum);

    printf("The maximum overlap starts in year %d.\n",
           bestYear);

    return 0;
}