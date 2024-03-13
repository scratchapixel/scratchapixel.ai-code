#include <iostream>
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime> // For std::time()

// Function to calculate the value of the given parabolic equation
double f(double x) {
    return 0.5 * x * x - 2 * x + 2;
}

// Derivative of the parabolic equation
double df(double x) {
    return x - 2;
}

int main() {
    std::srand(13); // Seed the random number generator
    double x = std::rand() % 100 / 10.0 - 5; // Start at a random point between -5 and 5
    double learning_rate = 0.01; // Learning rate
    double threshold = 0.001; // Threshold for cost function value to stop iterating
    int max_iterations = 1000; // Maximum number of iterations to prevent infinite loops
    int iteration = 0;

    double cost = f(x); // Calculate initial cost

    while (cost > threshold && iteration < max_iterations) {
        x -= learning_rate * df(x); // Adjust x based on the derivative of the cost function
        cost = f(x); // Recalculate cost after updating x
        iteration++;

        std::cout << "Iteration " << iteration << ": x = " << x << ", Cost = " << cost << std::endl;
    }

    std::cout << "Stopped at iteration " << iteration << " with x = " << x << " and Cost = " << cost << std::endl;

    return 0;
}