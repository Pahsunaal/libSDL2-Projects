#pragma once
#include <utility>
#include <cmath>

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
}