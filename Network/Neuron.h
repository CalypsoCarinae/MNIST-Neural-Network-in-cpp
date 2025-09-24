#pragma once
#include <iostream>
#include <vector>
#include <random>

class Neuron {
private:
    std::vector<float> weights;
    float bias = 0.0;

    float last_output = 0.0;

public:
    Neuron();
    ~Neuron();
    Neuron(int connections);

    double sigmoid(double sum);
    double sigmoid_derivative(double sum);
    double sum(const std::vector<float>& input);
    void update(double lr, double delta, const std::vector<float> input);
    std::vector<float> getWeights();
    float getBias();
};