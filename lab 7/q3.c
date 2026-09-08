#include <stdio.h>
#include <limits.h>

long long dp[100];
int split[100];

void hanoi3(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

void computeDP(int n)
{
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k] +
                ((1LL << (i - k)) - 1);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }
}

void reve(int n, char source, char destination,
          char aux1, char aux2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    int k = split[n];

    // Move k smaller disks to auxiliary peg
    reve(k, source, aux1, destination, aux2);

    // Move remaining disks using 3 pegs
    hanoi3(n - k, source, destination, aux2);

    // Move k disks from auxiliary peg to destination
    reve(k, aux1, destination, source, aux2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    computeDP(n);

    printf("\nMinimum number of moves = %lld\n\n",
           dp[n]);

    printf("Sequence of moves:\n");

    reve(n, 'A', 'D', 'B', 'C');

    return 0;
}