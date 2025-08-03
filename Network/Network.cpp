#include "pch.h"
#include <iostream>
#include <vector>
#include "Neuron.h"

using t_network = std::vector<std::vector<Neuron>>;

class Network {
private:
    t_network network;

public:
    Network(std::vector<int> size) {
        if (size[0] != 784 || size[size.size() - 1] != 10) {
            std::cerr << "NETWORK ERROR: Invalid network size.\n\n";
        }

        network.resize(size.size() - 1);
        for (int i = 1; i < size.size(); i++) network[i].resize(size[i]);
        for (int i = 0; i < size.size(); i++) {
            for (int j = 0; j < network[i].size(); j++) {
                network[i][j] = Neuron(size[i - 1]);
            }
        }
    }

    ~Network() {};

    //TODO
};