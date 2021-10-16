#pragma once

#include <utility>
#include <cmath>
#include <fstream>


namespace Utils {
	const double pi = 3.14159265358979323846;

	constexpr double degToRad(double deg) {
		return deg * (pi / 180);
	}
	std::pair<double,double> dirLenToVector(double direction, double length) {
		std::pair<double, double> pair{};
		double rad = degToRad(direction);
		pair.first = length * std::cos(rad);
		pair.second = length * std::sin(rad);
		return pair;
	}

	std::string* getStringFromFile(const char* filename) {
		std::ifstream ifs(filename);
		std::string* content = new std::string;
		(*content).assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		return content;
	}
}