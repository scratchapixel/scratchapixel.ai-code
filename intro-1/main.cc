// (c) scratchapixel - 2024
// Distributed under the terms of the CC BY-NC-ND 4.0 License.
// https://creativecommons.org/licenses/by-nc-nd/4.0/
// save to main.cc and compile with: clang++ -Wall -Wextra -o main.exe main.cc

#include <random>
#include <iostream>
#include <chrono>

double data[][2] = {
	{0, 0},
	{1, 2},
	{2, 4},
	{3, 6},
	{4, 8}
};

double CostFunc(double w) {
    size_t data_size = sizeof(data) / sizeof(data[0]); // Calculate the number of elements in the array
	double cost = 0;
    for (size_t i = 0; i < data_size; ++i) {
        double x = data[i][0];
        double y = x * w;
		double dy = y - data[i][1];
		cost += dy * dy;
    }
	return cost / data_size;
}

int main() {
	std::random_device rd;
    auto seed = 13;//std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(0.0f, 10.0f);
	double w = dis(gen);
    std::cout << "Random w: " << w << std::endl;

	double step_size = 0.01;
	double h = 0.001;
	for (size_t i = 0; i < 1e5; ++i) {
		double deriv_cost = (CostFunc(w + h) - CostFunc(w)) / h;
		w -= deriv_cost * step_size;
		std::cerr << "Cost: " << CostFunc(w) << ", w: " << w << std::endl;
	}
	return 0;
}
