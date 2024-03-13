// save to main.cc and compile with: clang++ -Wall -Wextra -o main.exe main.cc
#include <random>
#include <iostream>
#include <chrono>

float data[][2] = {
	{0, 0},
	{1, 2},
	{2, 4},
	{3, 6},
	{4, 8}
};

float CostFunc(float w) {
    size_t data_size = sizeof(data) / sizeof(data[0]); // Calculate the number of elements in the array
	float cost = 0;
    for (size_t i = 0; i < data_size; ++i) {
        float x = data[i][0];
        float y = x * w;
		float dy = y - data[i][1];
		cost += dy * dy;
    }
	return cost / data_size;
}

int main() {
	std::random_device rd;
    auto seed = 13;//std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(0.0f, 10.0f);
	float w = dis(gen);
    std::cout << "Random w: " << w << std::endl;

	float epsilon = 0.1;
	for (size_t n = 0; n < 10; n++) {
		w -= epsilon;
		std::cerr << "Cost: " << CostFunc(w) << std::endl;
	}

	return 0;
}
