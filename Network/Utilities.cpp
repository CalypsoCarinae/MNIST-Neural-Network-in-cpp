#include <iostream>
#include <vector>

using t_floatmatrix = std::vector<std::vector<float>>;

bool isConstShape(const t_floatmatrix& input) {
    int size = input[0].size();
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