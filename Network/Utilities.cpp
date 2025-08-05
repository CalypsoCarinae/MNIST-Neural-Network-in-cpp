#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

using t_floatmatrix = std::vector<std::vector<float>>;

bool isConstShape(const t_floatmatrix& input) {
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