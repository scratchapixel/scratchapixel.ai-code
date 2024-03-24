// (c) scratchapixel - 2024
// Distributed under the terms of the CC BY-NC-ND 4.0 License.
// https://creativecommons.org/licenses/by-nc-nd/4.0/
// save to main.cc and compile with: clang++ -Wall -Wextra -o main.exe main.cc

#include <random>
#include <iostream>
#include <chrono>
#include <cmath>

// XOR logic gate training data. First two elements are the inputs. Third
// element in the colum is the expected output.
float data[][3] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 1},
};

float Sigmoid(const float& x) {
	return 1.f / (1.f + std::exp(-x));
}

float CostFunc(float w1, float w2, float bias) {
    size_t data_size = sizeof(data) / sizeof(data[0]); // Calculate the number of elements in the array
	float cost = 0;
    for (size_t i = 0; i < data_size; ++i) {
        float x1 = data[i][0];
		float x2 = data[i][1];
        float y = Sigmoid(x1 * w1 + x2 * w2 + bias);
		float dy = y - data[i][2];
		cost += dy * dy;
    }
	return cost / data_size;
}

int main() {
	std::random_device rd;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(0, 1);
	float w1 = dis(gen);
	float w2 = dis(gen);
	float bias = dis(gen);

	float h = 0.1;
	float step_size = 0.1;
	
	for (size_t i = 0; i < 1e6; ++i) {
		float c = CostFunc(w1, w2, bias);
		float dw1 = (CostFunc(w1 + h, w2, bias) - c) / h;
		float dw2 = (CostFunc(w1, w2 + h, bias) - c) / h;
		float dbias = (CostFunc(w1, w2, bias + h) - c) / h;
		w1 -= dw1 * step_size;
		w2 -= dw2 * step_size;
		bias -= dbias * step_size;
	}
	std::cerr << w1 << " " << w2 << " " << bias << " " << CostFunc(w1, w2, bias) << std::endl;
	
	// testing our model
	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			std::cerr << i << " | " << j << " = " << Sigmoid(i * w1 + j * w2 + bias) << std::endl;  
		}
	}
	
	return 0;
}
