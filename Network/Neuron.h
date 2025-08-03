#pragma once
#include <iostream>
#include <vector>
#include <random>

class Neuron {
private:
    std::vector<float> weights;
    float bias = 0;
public:
    Neuron() {};
    Neuron(int connections) {}
    ~Neuron() {}
    double sigmoid(double sum) {}
    double sum(std::vector<float> input) {}
    void update(double lr, double delta, const std::vector<float> input) {}
    std::vector<float> getWeights() {}
    float getBias() {}
};