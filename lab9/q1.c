#include <stdio.h>

typedef struct
{
    int id;
    double value;
    double weight;
    double lambda;
    double fraction;
    double density;
} Item;

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        items[i].fraction = 0.0;

        printf("Enter value, weight and decay rate for item %d: ",
               i + 1);

        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].lambda);
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    double remaining = W;
    double totalValue = 0.0;
    int time = 0;

    printf("\nSelected items:\n");

    while (remaining > 0)
    {
        int best = -1;
        double bestDensity = -1e100;

        for (int i = 0; i < n; i++)
        {
            if (items[i].fraction == 1.0)
                continue;

            double currentDensity =
                (items[i].value / items[i].weight)
                - items[i].lambda * time;

            if (currentDensity > bestDensity)
            {
                bestDensity = currentDensity;
                best = i;
            }
        }

        if (best == -1 || bestDensity <= 0)
            break;

        double take = items[best].weight;

        if (take > remaining)
            take = remaining;

        items[best].fraction =
            take / items[best].weight;

        items[best].density = bestDensity;

        totalValue += take * bestDensity;
        remaining -= take;

        printf("Time %d: Item %d, fraction = %.4f, "
               "effective density = %.4f\n",
               time,
               items[best].id,
               items[best].fraction,
               bestDensity);

        time++;
    }

    printf("\nMaximum obtained value = %.4lf\n", totalValue);

    return 0;
}