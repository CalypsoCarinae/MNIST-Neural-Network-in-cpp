#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

using t_floatmatrix = std::vector<std::vector<float>>;

bool is_const_shape(const t_floatmatrix& input) {
    size_t size = input[0].size();
    for (int i = 0; i < input.size(); i++)
        if (size != input[i].size()) return false;
    return true;
}

void normalize(std::vector<float>& input) {
    float max = input[0];
    for (int i = 1; i < input.size(); i++)
        max = input[i] > max ? input[i] : max;
    for (float el : input) el /= max;
}

int read_int32(std::ifstream& stream) {
    unsigned char bytes[4];
    stream.read((char*)bytes, 4);
    int result = int(bytes[0]) << 24 | int(bytes[1]) << 16 | int(bytes[2]) << 8 | int(bytes[3]);
    return result;
}

void print_image(const t_floatmatrix& imgs, const size_t& amnt) {
    for (int i = 0; i < amnt; i++) {
        std::cout << "(";
        for (int j = 0; j < imgs[i].size(); j++) {
            std::cout << imgs[i][j] << ", ";
            if (j % 28 == 0 && j != 0) std::cout << "\n";
        }
        std::cout << ")\n\n";
    }
}

bool are_same_size(t_floatmatrix m1, t_floatmatrix m2) {
    if (m1.size() != m2.size()) return false;
    for (int i = 0; i < m1.size(); i++) if (m1[i].size() != m2[i].size()) return false;
    return true;
}

int maxID(const std::vector<float>& input) {
    int ID = 0;
    for (int i = 1; i < input.size(); i++) if (input[i] > input[ID]) ID = i;

    return ID;
}