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
    Network() {}

    Network(const std::vector<int> size) {
        if (size[0] != 784 || size[size.size() - 1] != 10) {
            // Replace with an actual exception
            std::cerr << "Network Initializing Error: Invalid network size.\n\n";
        }

        int layer_count = size.size() - 1;
        network.resize(layer_count);

        for (int i = 0; i < layer_count; i++) {
            int curr = size[i + 1];
            int prev = size[i];

            network[i].resize(curr);
            for (int j = 0; j < curr; j++) network[i][j] = Neuron(prev);
        }
    }

    ~Network() {}
    t_floatmatrix forward_propagation(const std::vector<float>& input);
    void backward_propagation(const t_floatmatrix& neuron_impulses, const int& label, float lr);
    void training(t_floatmatrix& input_data, const std::vector<int>& label_data, int epoch, float lr = 0.1);
};