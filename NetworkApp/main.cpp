#include <iostream>
#include <random>
#include <vector>
#include <Network.h>
#include <Utilities.h>
#include <FileReader.h>

using t_floatmatrix = std::vector<std::vector<float>>;

//temporary, to check whether files are being read correctly

void tempFileTest() {
    size_t size = 5;
    t_floatmatrix training_images;

    if (!mnist_image_loader("dataset/train-images.idx3-ubyte", training_images)) {
        std::cerr << "didn't work lol\n\n";
    }

    print_image(training_images, size);

    std::vector<int> labels;

    if (!mnist_label_loader("dataset/train-labels.idx1-ubyte", labels)) {
        std::cerr << "didn't work lol\n\n";
    }

    std::cout << "\n\n\n\n";

    for (int i = 0; i < size; i++) {
        std::cout << labels[i] << "\n";
    }
}

int main()
{
    srand(time(NULL));

    const std::vector<int> MNIST_size = { 784, 128, 64, 10 };
    Network test = Network(MNIST_size);

    // testing
    //tempFileTest();
}