#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Utilities.h"

using t_floatmatrix = std::vector<std::vector<float>>;

bool mnist_image_loader(const std::string& filename, t_floatmatrix& images) {
	std::ifstream image_file(filename, std::ios::binary);

	if (!image_file.is_open()) {
		// Exception later
		std::cerr << "Opening file exception.\n\n";
		return false;
	}

	int ver = read_int32(image_file);

	if (ver != 2051) {
		// Exception later
		std::cerr << "Verification number invalid.\n\n";
		return false;
	}

	int amount = read_int32(image_file);
	int r = read_int32(image_file);				// row
	int c = read_int32(image_file);				// col

	if (c != 28 || r != 28) {
		// Yeah
		std::cerr << "Size invalid.\n\n";
		return false;
	}

	images.resize(amount, std::vector<float>(784));

	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < 784; j++) {
			unsigned char pix;
			image_file.read((char*)&pix, 1);
			images[i][j] = float(pix);
		}
	}

	return true;
}

bool mnist_label_loader(const std::string& filename, std::vector<int>& labels) {
	std::ifstream label_file(filename, std::ios::binary);

	if (!label_file.is_open()) {
		// Exception later
		std::cerr << "Opening file exception.\n\n";
		return false;
	}

	int ver = read_int32(label_file);

	if (ver != 2049) {
		// Exception later
		std::cerr << "Verification number invalid.\n\n";
		return false;
	}

	int amount = read_int32(label_file);
	labels.resize(amount);

	for (int i = 0; i < amount; i++) {
		unsigned char label;
		label_file.read((char*)&label, 1);
		labels[i] = label;
	}

	return true;
}