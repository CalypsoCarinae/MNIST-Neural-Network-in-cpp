#pragma once
#include <iostream>
#include <vector>
#include "Neuron.h"

using t_network = std::vector<std::vector<Neuron>>;
using t_floatmatrix = std::vector<std::vector<float>>;

class Network {
private:
    t_network network;

public:
    Network();
    Network(const std::vector<int> size);
    ~Network();

    int predict(const std::vector<float>& image);
    t_floatmatrix forward_propagation(const std::vector<float>& input);
    void backward_propagation(const t_floatmatrix& neuron_impulses, const int& label, float lr);
    void training(t_floatmatrix& input_data, const std::vector<int>& label_data, int epoch = 1, float lr = 0.1, bool printProgress = false);
    std::vector<std::vector<std::vector<float>>> get_all_weights();
    std::vector<int> get_size();
};