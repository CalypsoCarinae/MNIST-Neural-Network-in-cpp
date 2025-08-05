#pragma once
#include <iostream>
#include <vector>
#include <string>

using t_floatmatrix = std::vector<std::vector<float>>;

bool mnist_image_loader(const std::string& filename, t_floatmatrix& images);
bool mnist_label_loader(const std::string& filename, std::vector<int>& labels);