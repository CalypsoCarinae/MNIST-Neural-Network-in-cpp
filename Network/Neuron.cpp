#include "pch.h"
#include "Neuron.h"
#include <cmath>
#include <iostream>

Neuron::Neuron() {}

Neuron::~Neuron() {}

Neuron::Neuron(int connections) {
    weights.resize(connections);
    for (int i = 0; i < connections; i++) {
        weights[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }
    bias = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
}

double Neuron::sigmoid(double sum) {
    return 1.0 / (1.0 + std::exp(-sum));
}

double Neuron::sigmoid_derivative(double sum) {
    double s = sigmoid(sum);
    return s * (1.0 - s);
}

double Neuron::sum(const std::vector<float>& input) {
    if (input.size() != weights.size()) {
        std::cerr << "Neuron Summing Exception: Dimensions don't match.\n\n";
    }

    double result = 0.0;
    for (int i = 0; i < weights.size(); i++) {
        result += input[i] * weights[i];
    }
    result += bias;
    return result;
}

void Neuron::update(double lr, double delta, const std::vector<float> input) {
    for (int i = 0; i < weights.size(); i++) {
        weights[i] -= lr * delta * input[i];
    }
    bias -= lr * delta;
}

std::vector<float> Neuron::getWeights() {
    return weights;
}

float Neuron::getBias() {
    return bias;
}