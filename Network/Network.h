#pragma once
#include <iostream>
#include <vector>
#include "Neuron.h"

using t_network = std::vector<std::vector<Neuron>>;
using t_floatmatrix = std::vector<std::vector<float>>;

bool isConstShape(const t_floatmatrix& input);
void normalize(std::vector<float>& input);

class Network {
private:
    t_network network;

public:
    Network();
    Network(std::vector<int> size);
    ~Network();
    t_floatmatrix forward_propagation(const std::vector<float>& input);
    void backward_propagation(const t_floatmatrix& neuron_impulses, const int& label, float lr);
    void training(t_floatmatrix& input_data, const std::vector<int>& label_data, int epoch, float lr = 0.1);
};