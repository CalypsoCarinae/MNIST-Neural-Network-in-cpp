#include <iostream>
#include <random>
#include <vector>
#include <Network.h>
#include <Utilities.h>
#include <DatasetReader.h>

#define SIZE 50

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
    
    training_images.resize(2000);

    my_network.training(training_images, labels, 10, 0.1f, true);

    t_floatmatrix prediction_images;
    std::vector<int> prediction_labels;

    if (!mnist_image_loader("dataset/t10k-images.idx3-ubyte", prediction_images)) {
        std::cerr << "Predicting data loading error.\n\n";
    }

    if (!mnist_label_loader("dataset/t10k-labels.idx1-ubyte", prediction_labels)) {
        std::cerr << "Predicting labels loading error.\n\n";
    }

    float percentage = 0.0f;

    for (int i = 0; i < SIZE; i++) {
        int prediction = my_network.predict(prediction_images[i]);
        std::cout << "\n\nPrediction: " << prediction << "\nActual: " << prediction_labels[i];
        if (prediction == prediction_labels[i]) percentage++;
    }

    percentage /= SIZE;
    percentage *= 100.0f;

    std::cout << "\n" << percentage << "% of predictions were correct.";
}