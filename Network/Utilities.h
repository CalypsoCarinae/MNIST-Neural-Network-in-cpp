#pragma once
#include <iostream>
#include <vector>

using t_floatmatrix = std::vector<std::vector<float>>;

bool isConstShape(const t_floatmatrix& input);
void normalize(std::vector<float>& input);