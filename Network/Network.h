#pragma once
#include <iostream>
#include <vector>
#include "Neuron.h"

using t_network = std::vector<std::vector<Neuron>>;

class Network {
private:
    t_network network;

public:
    Network(std::vector<int> size) {}
    ~Network() {};
};