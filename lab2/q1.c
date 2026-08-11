#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to simulate coin tosses and return the observed probability of getting HEAD
double simulate_coin(double bias, int trials) {
    int heads = 0;
    for (int i = 0; i < trials; i++) {
        // Generate a random float between 0.0 and 1.0
        double rand_val = (double)rand() / RAND_MAX;
        if (rand_val < bias) {
            heads++;
        }
    }
    return (double)heads / trials;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    
    int trials = 1000000; // 1 million trials for accurate statistical approximation
    
    // 1. Fair coin experiment (bias = 0.5)
    double fair_bias = 0.5;
    double fair_prob = simulate_coin(fair_bias, trials);
    
    // 2. Biased coin experiment (e.g., bias = 0.75)
    double biased_bias = 0.75;
    double biased_prob = simulate_coin(biased_bias, trials);
    
    printf("--- Coin Tossing Simulation (Trials: %d) ---\n", trials);
    printf("Fair Coin (Target Bias: %.2f) -> Observed HEAD Probability: %.5f\n", fair_bias, fair_prob);
    printf("Biased Coin (Target Bias: %.2f) -> Observed HEAD Probability: %.5f\n", biased_bias, biased_prob);
    
    return 0;
}