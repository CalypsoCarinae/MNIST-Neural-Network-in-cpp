#include "pch.h"
#include "Network.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

Network::Network() {}

Network::Network(const std::vector<int> size) {
    if (size[0] != 784 || size[size.size() - 1] != 10) {
        std::cerr << "Network Initializing Error: Invalid network size.\n\n";
    }

    int layer_count = size.size() - 1;
    network.resize(layer_count);

    for (int i = 0; i < layer_count; i++) {
        int curr = size[i + 1];
        int prev = size[i];

        network[i].resize(curr);
        for (int j = 0; j < curr; j++) {
            network[i][j] = Neuron(prev);
        }
    }
}

Network::~Network() {}

int Network::predict(const std::vector<float>& image) {
    if (image.size() != 784) {
        std::cerr << "Image Size Error: Not 28x28.\n\n";
    }

    auto result = forward_propagation(image);
    return maxID(result[result.size() - 1]);
}

t_floatmatrix Network::forward_propagation(const std::vector<float>& input) {
    int layer_count = network.size();
    t_floatmatrix neuron_impulses(layer_count + 1);
    neuron_impulses[0] = input;

    for (int i = 0; i < layer_count; i++) {
        neuron_impulses[i + 1].resize(network[i].size());
        for (int j = 0; j < network[i].size(); j++) {
            neuron_impulses[i + 1][j] =
                network[i][j].sigmoid(network[i][j].sum(neuron_impulses[i]));
        }
    }

    return neuron_impulses;
}

void Network::backward_propagation(const t_floatmatrix& neuron_impulses, const int& l, float lr) {
    int layer_count = network.size();
    std::vector<int> labels(10, 0);
    labels[l] = 1;

    t_floatmatrix delta(layer_count);
    const std::vector<float>& output = neuron_impulses[layer_count];

    if (output.size() != labels.size()) {
        std::cerr << "Network Training Error: Backpropagation: Output amount of neurons not equal to 10.\n\n";
    }

    // Output layer deltas
    delta[layer_count - 1].resize(output.size());
    for (int i = 0; i < output.size(); i++) {
        float neuron_sum = network[layer_count - 1][i].sum(neuron_impulses[layer_count - 1]);
        float Delta = (output[i] - labels[i]) * network[layer_count - 1][i].sigmoid_derivative(neuron_sum);
        delta[layer_count - 1][i] = Delta;
    }

    // Hidden layer deltas
    for (int li = layer_count - 2; li >= 0; li--) {
        delta[li].resize(network[li].size());
        for (int i = 0; i < delta[li].size(); i++) {
            float sum = 0.0f;
            for (int j = 0; j < network[li + 1].size(); j++) {
                sum += network[li + 1][j].getWeights()[i] * delta[li + 1][j];
            }
            float neuron_sum = network[li][i].sum(neuron_impulses[li]);
            float Delta = sum * network[li][i].sigmoid_derivative(neuron_sum);
            delta[li][i] = Delta;
        }
    }

    // Weight updates
    for (int li = 0; li < layer_count; li++) {
        for (int i = 0; i < network[li].size(); i++) {
            network[li][i].update(lr, delta[li][i], neuron_impulses[li]);
        }
    }
}

void Network::training(t_floatmatrix& input_data, const std::vector<int>& label_data, int epoch, float lr, bool printProgress) {
    if (!is_const_shape(input_data) || input_data[0].size() != 784 || input_data.size() != label_data.size()) {
        std::cerr << "Network Training Error: Invalid Input Data/Label Data.\n\n";
    }

    for (auto& in : input_data) {
        normalize(in);
    }

    for (int e = 0; e < epoch; e++) {
        for (int s = 0; s < input_data.size(); s++) {
            std::vector<float> curr_input = input_data[s];
            int label = label_data[s];

            auto neuron_impulses = forward_propagation(curr_input);
            backward_propagation(neuron_impulses, label, lr);

            if (printProgress) {
                std::cout << "Training progress -- "
                    << (((float)e / epoch) + (1.0f / epoch) * ((float)s / input_data.size())) * 100.0f
                    << "% \n\n";
            }
        }
    }
}

std::vector<std::vector<std::vector<float>>> Network::get_all_weights() {
    std::vector<std::vector<std::vector<float>>> weights;
    weights.resize(network.size());

    for (int i = 0; i < network.size(); i++) {
        weights[i].resize(network[i].size());
    }

    for (int i = 0; i < network.size(); i++) {
        for (int j = 0; j < network[i].size(); j++) {
            std::vector<float> curr_weights = network[i][j].getWeights();
            for (int k = 0; k < curr_weights.size(); k++) {
                weights[i][j].push_back(curr_weights[k]);
            }
        }
    }

    return weights;
}

std::vector<int> Network::get_size() {
    std::vector<int> sizes;
    for (int i = 0; i < network.size(); i++) {
        sizes.push_back(network[i].size());
    }
    return sizes;
}