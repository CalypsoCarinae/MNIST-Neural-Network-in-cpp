#include "pch.h"
#include <iostream>
#include <vector>
#include <random>

class Neuron {
private:
    std::vector<float> weights;
    float bias = 0.0;
public:
    double sigmoid(double sum) {
        return 1.0 / (1.0 + std::exp(-sum));
    }

    double sigmoid_derivative(double sum) {
        return sigmoid(sum) * (1.0 - sigmoid(sum));
    }

    double sum(const std::vector<float>& input) {
        if (input.size() != weights.size()) {
            // Replace with an exception
            std::cerr << "Neuron Summing Exception: Dimensions don't match.\n\n";
        }

        double result = 0.0;
        for (int i = 0; i < weights.size(); i++) result += input[i] * weights[i];
        result += bias;
        return result;
    }

    void update(double lr, double delta, const std::vector<float> input) {
        for (int i = 0; i < weights.size(); i++) weights[i] -= lr * delta * input[i];
        bias -= lr * delta;
    }

    std::vector<float> getWeights() {
        return weights;
    }

    float getBias() {
        return bias;
    }
};