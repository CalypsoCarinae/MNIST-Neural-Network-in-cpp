#include "pch.h"
#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Utilities.h"

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

    t_floatmatrix forward_propagation(const std::vector<float>& input) {
        int layer_count = network.size();
        t_floatmatrix neuron_impulses(layer_count + 1);
        neuron_impulses[0] = input;

        for (int i = 0; i < layer_count; i++) {
            neuron_impulses[i + 1].resize(network[i].size());
            for (int j = 0; j < network[i].size(); j++)
                neuron_impulses[i + 1][j] = network[i][j].sigmoid(network[i][j].sum(neuron_impulses[i]));
        }
    }

    void backward_propagation(const t_floatmatrix& neuron_impulses, const int& label, float lr) {
        int layer_count = network.size();
        std::vector<int> labels(10, 0);
        labels[label] = 1;

        t_floatmatrix delta(layer_count);

        const std::vector<float>& output = neuron_impulses[layer_count];

        if (output.size() != labels.size()) {
            // Actual exception here too sometime
            std::cerr << "Network Training Error: Backpropagation: Output amount of neurons not equal to 10.\n\n";
        }

        // Last layer of deltas

        delta[layer_count - 1].resize(output.size());

        for (int i = 0; i < output.size(); i++) {
            float out = output[i];
            float neuron_sum = network[layer_count - 1][i].sum(neuron_impulses[layer_count - 1]);

            float Delta = (out - labels[i]) * network[layer_count - 1][i].sigmoid_derivative(neuron_sum);
            delta[layer_count - 1][i] = Delta;
        }

        // Hidden layers of deltas

        for (int l = layer_count - 2; l >= 0; l--) {
            delta[l].resize(network[l].size());

            for (int i = 0; i < delta[l].size(); i++) {
                float sum = 0.0;
                for (int j = 0; j < network[l + 1].size(); j++) {
                    sum += network[l + 1][j].getWeights()[i] * delta[l + 1][j];
                }

                float neuron_sum = network[l][i].sum(neuron_impulses[l]);
                float Delta = sum * network[l][i].sigmoid_derivative(neuron_sum);
                delta[l][i] = Delta;
            }
        }

        // Updates
        for (int l = 0; l < layer_count; l++)
            for (int i = 0; i < network[l].size(); i++)
                network[l][i].update(lr, -delta[l][i], neuron_impulses[l]);
    }

    void training(t_floatmatrix& input_data, const std::vector<int>& label_data, int epoch, float lr = 0.1) {
        if (!isConstShape(input_data) || input_data[0].size() != 784 || input_data.size() != label_data.size()) {
            // Replace with an actual exception
            std::cerr << "Network Training Error: Invalid Input Data/Label Data.\n\n";
        }

        // Normalizing done inside, maybe that's not the best idea? idk
        for (auto in : input_data) normalize(in);

        for (int e = 0; e < epoch; e++) {
            for (int s = 0; s < input_data.size(); s++) {
                std::vector<float> curr_input = input_data[s];
                int label = label_data[s];
                
                auto neuron_impulses = forward_propagation(curr_input);

                backward_propagation(neuron_impulses, label, lr);
            }
        }
    }
};