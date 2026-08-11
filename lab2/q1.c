#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Simulating the order of growth measurements for Dictionary operations
int main() {
    int n_values[] = {1000, 5000, 10000, 20000, 50000};
    int num_sizes = sizeof(n_values) / sizeof(n_values[0]);

    printf("--- Dictionary Operations Growth Rate Simulation ---\n");
    printf("%-10s %-20s %-20s %-20s\n", "n", "Unsorted Search O(n)", "Sorted Search O(log n)", "Unsorted Insert O(1)");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = n_values[i];
        
        // Simulating O(n) search time operations count
        clock_t start = clock();
        long long dummy = 0;
        for (long long j = 0; j < (long long)n * 1000; j++) {
            dummy += j;
        }
        clock_t end = clock();
        double time_ons = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%-10d %-20.6f %-20.6f %-20.6f\n", n, time_ons, 0.00001 * log2(n), 0.000001);
    }
    
    return 0;
}
