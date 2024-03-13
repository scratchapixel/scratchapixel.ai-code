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

int main() {
	std::random_device rd;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(0.0f, 10.0f);
	float w = dis(gen);

    std::cout << "Random w: " << w << std::endl;

    size_t data_size = sizeof(data) / sizeof(data[0]); // Calculate the number of elements in the array
    for (size_t i = 0; i < data_size; ++i) {
        float x = data[i][0];
        float y = x * w;
        std::cerr << "actual: " << y << ", expected: " << data[i][1] << std::endl;
    }

	return 0;
}
