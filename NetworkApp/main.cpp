#include <iostream>
#include <random>
#include <vector>
#include <Network.h>
#include <Utilities.h>
#include <DatasetReader.h>

using t_floatmatrix = std::vector<std::vector<float>>;

int main()
{
    srand(time(NULL));
    
    const std::vector<int> MNIST_size = { 784, 128, 64, 10 };
    Network my_network = Network(MNIST_size);


    t_floatmatrix training_images;
    std::vector<int> labels;

    if (!mnist_image_loader("dataset/train-images.idx3-ubyte", training_images)) {
        std::cerr << "Training data loading error.\n\n";
    }

    if (!mnist_label_loader("dataset/train-labels.idx1-ubyte", labels)) {
        std::cerr << "Training labels loading error.\n\n";
    }

    training_images.resize(1000);

    my_network.training(training_images, labels, 10, 0.1f, true);

    t_floatmatrix prediction_images;
    std::vector<int> prediction_labels;

    if (!mnist_image_loader("dataset/t10k-images.idx3-ubyte", training_images)) {
        std::cerr << "Predicting data loading error.\n\n";
    }

    if (!mnist_label_loader("dataset/t10k-labels.idx1-ubyte", labels)) {
        std::cerr << "Predicting labels loading error.\n\n";
    }

    std::cout << "I reached this checkpoint!\n\n";

    for (int i = 0; i < 5; i++) std::cout << "\n\n Prediction: " << my_network.predict(prediction_images[i]) << "\nActual: " << prediction_labels[i];
}