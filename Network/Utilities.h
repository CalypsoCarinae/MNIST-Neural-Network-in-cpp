#pragma once
#include <iostream>
#include <vector>

using t_floatmatrix = std::vector<std::vector<float>>;

bool is_const_shape(const t_floatmatrix& input);
int read_int32(std::ifstream& stream);
void print_image(const t_floatmatrix& imgs, const size_t& amnt);
bool are_same_size(t_floatmatrix m1, t_floatmatrix m2);
int maxID(const std::vector<float>& input);