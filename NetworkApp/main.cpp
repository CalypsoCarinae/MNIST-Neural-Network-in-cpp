#include <iostream>
#include <random>
#include <Network.h>

int main()
{
    srand(time(NULL));

    const std::vector<int> MNIST_size = { 784, 128, 64, 10 };

    Network test = Network(MNIST_size);


    //TODO obviously
}