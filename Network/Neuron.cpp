#include "pch.h"
#include <iostream>
#include <vector>
#include <random>

class Neuron {
private:
    std::vector<float> weights;
    float bias = 0;
public:
    Neuron() {};

    Neuron(int connections) {
        weights.resize(connections);
        for (int i = 0; i < connections; i++) weights[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        bias = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }

    ~Neuron() {}

    double sigmoid(double sum) {
        return 1.0 / (1.0 + std::exp(sum));
    }

    double sum(std::vector<float> input) {
        double result = 0.0;
        for (int i = 0; i < weights.size(); i++) result += input[i] * weights[i];
        result += bias;
        return result;
    }

    void update(double lr, double delta, const std::vector<float> input) {
        for (int i = 0; i < weights.size(); i++) weights[i] += lr * delta * input[i];
        bias += lr * delta;
    }

    std::vector<float> getWeights() {
        return weights;
    }

    float getBias() {
        return bias;
    }
};