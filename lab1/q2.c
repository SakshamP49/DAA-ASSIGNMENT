#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double simulate_coin(double bias, int trials) {
    int heads = 0;
    for (int i = 0; i < trials; i++) {
        double rand_val = (double)rand() / RAND_MAX;
        if (rand_val < bias) {
            heads++;
        }
    }
    return (double)heads / trials;
}

int main() {
    srand(time(NULL));
    int trials = 1000000;
    
    double fair_prob = simulate_coin(0.5, trials);
    double biased_prob = simulate_coin(0.75, trials);
    
    printf("Fair coin (bias 0.5) observed HEAD probability: %f\n", fair_prob);
    printf("Biased coin (bias 0.75) observed HEAD probability: %f\n", biased_prob);
    
    return 0;
}