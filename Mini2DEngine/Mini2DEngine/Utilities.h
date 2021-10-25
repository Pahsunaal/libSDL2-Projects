#ifndef H_UTILITIES
#define H_UTILITIES

#include <utility>
#include <cmath>
#include <fstream>
#include <rapidjson/document.h>


namespace Utils {
	const double pi = 3.14159265358979323846;;

	constexpr double degToRad(double deg);
	std::pair<double, double> dirLenToVector(double direction, double length);

	std::string* getStringFromFile(const char* filename);

	rapidjson::Document* parseJSON(const char* pathToFile);

	double randDouble(double max);

	double choose(double i, double j);
}

#endif // !H_UTILITIES