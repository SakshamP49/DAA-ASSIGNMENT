#include <stdio.h>

int minimumMoves(int n)
{
    int totalCoins;
    int moves;

    // Total number of coins in n rows
    totalCoins = n * (n + 1) / 2;

    // Minimum number of coins to move
    moves = totalCoins / 3;

    return moves;
}

int main()
{
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    int totalCoins = n * (n + 1) / 2;

    printf("Total coins = %d\n", totalCoins);

    printf("Minimum moves = %d\n", minimumMoves(n));

    return 0;
}