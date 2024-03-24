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

struct XorModel {
	XorModel() {
		std::random_device rd;
		auto seed = 13;//std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 gen(seed);
		std::uniform_real_distribution<float> dis(0, 1);

		or_w1 = dis(gen);
		or_w2 = dis(gen);
		or_b = dis(gen);

		nand_w1 = dis(gen);
		nand_w2 = dis(gen);
		nand_b = dis(gen);

		and_w1 = dis(gen);
		and_w2 = dis(gen);
		and_b = dis(gen);
	}
	void print() {
		std::cerr << or_w1 << " " << or_w2 << " " << or_b << std::endl;
		std::cerr << nand_w1 << " " << nand_w2 << " " << nand_b << std::endl;
		std::cerr << and_w1 << " " << and_w2 << " " << and_b << std::endl;
	}
	float or_w1;
    float or_w2;
    float or_b;

    float nand_w1;
    float nand_w2;
    float nand_b;

    float and_w1;
    float and_w2;
    float and_b;
};

float ForwardPass(XorModel xor_model, float x1, float x2) {
    float or_output = Sigmoid(
				   xor_model.or_w1 * x1 + 
				   xor_model.or_w2 * x2 + 
				   xor_model.or_b);
    float nand_output = Sigmoid(
				   xor_model.nand_w1 * x1 + 
				   xor_model.nand_w2 * x2 + 
				   xor_model.nand_b);
	// and
    return Sigmoid(xor_model.and_w1 * or_output + 
                   xor_model.and_w2 * nand_output + 
                   xor_model.and_b);
}

float CostFunc(XorModel xor_model) {
    size_t data_size = sizeof(data) / sizeof(data[0]); // Calculate the number of elements in the array
    float cost = 0;
    for (size_t i = 0; i < data_size; ++i) {
        float y = ForwardPass(xor_model, data[i][0], data[i][1]);
        float dy = y - data[i][2];
        cost += dy * dy;
    }
    return cost / data_size;
}

constexpr float h = 0.1;
constexpr float step_size = 0.1;

// A Gradient Descent pass. We frit calculate the gradient
// and the substract the graident wiehgt and biases from theor multiplied by the leatnering rate )(the step size)
// resdpective weight and biases from the model
void AdjustWeightsAndBiases(XorModel &m) {
	float cost = CostFunc(m);
	float temp{0};
	XorModel gradient;
	
	// OR
	temp = m.or_w1;
	m.or_w1 += h;
	gradient.or_w1 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's or_w1 weioght
	m.or_w1 = temp;
	
	temp = m.or_w2;
	m.or_w2 += h;
	gradient.or_w2 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's or_w1 weioght
	m.or_w2 = temp;
	
	temp = m.or_b;
	m.or_b += h;
	gradient.or_b = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's or_w1 weioght
	m.or_b = temp;

	// NAND
	temp = m.nand_w1;
	m.nand_w1 += h;
	gradient.nand_w1 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's nand_w1 weioght
	m.nand_w1 = temp;

	temp = m.nand_w2;
	m.nand_w2 += h;
	gradient.nand_w2 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's nand_w1 weioght
	m.nand_w2 = temp;

	temp = m.nand_b;
	m.nand_b += h;
	gradient.nand_b = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's nand_w1 weioght
	m.nand_b = temp;

	// AND
	temp = m.and_w1;
	m.and_w1 += h;
	gradient.and_w1 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's and_w1 weioght
	m.and_w1 = temp;

	temp = m.and_w2;
	m.and_w2 += h;
	gradient.and_w2 = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's and_w1 weioght
	m.and_w2 = temp;

	temp = m.and_b;
	m.and_b += h;
	gradient.and_b = (CostFunc(m) - cost) / h; // calculate partifial derivative of cost functin with respect to model's and_w1 weioght
	m.and_b = temp;

	m.or_w1 -= gradient.or_w1 * step_size;
	m.or_w2 -= gradient.or_w2 * step_size;
	m.or_b -= gradient.or_b * step_size;
	
	m.nand_w1 -= gradient.nand_w1 * step_size;
	m.nand_w2 -= gradient.nand_w2 * step_size;
	m.nand_b -= gradient.nand_b * step_size;
	
	m.and_w1 -= gradient.and_w1 * step_size;
	m.and_w2 -= gradient.and_w2 * step_size;
	m.and_b -= gradient.and_b * step_size;
}

int main() {
	XorModel xor_model;

	// Training
	for (size_t i = 0; i < 1e5; ++i) {
		AdjustWeightsAndBiases(xor_model);
	}

	// Prediction
	std::cerr << "Cost: " << CostFunc(xor_model) << std::endl;
	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			std::cerr << i << " ^ " << j << " = " << ForwardPass(xor_model, i, j) << std::endl;  
		}
	}
	
	return 0;
}
