//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DUtilitiesImp.h"

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Utils;





//--------------------------------------------------
//  degToRad : .
//--------------------------------------------------
const double Utils::degToRad(double deg)
{
	return deg * (pi / 180);
}





//--------------------------------------------------
//  dirLenToVector : .
//--------------------------------------------------
std::pair<double, double> Utils::dirLenToVector(double direction, double length)
{
	std::pair<double, double> pair{};
	double rad = degToRad(direction);

	// Basic trig to convert
	pair.first = length * std::cos(rad);
	pair.second = length * std::sin(rad);
	return pair;
}





//--------------------------------------------------
//  getStringFromFile : .
//--------------------------------------------------
std::string* Utils::getStringFromFile(const char* filename)
{
	std::ifstream ifs(filename);
	std::string* content = new std::string;
	(*content).assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	return content;
}





//--------------------------------------------------
//  parseJSON : .
//--------------------------------------------------
rapidjson::Document* Utils::parseJSON(const char* pathToFile)
{
	rapidjson::Document* document = new rapidjson::Document{};
	document->Parse(pathToFile);
	return document;
}





//--------------------------------------------------
//  randDouble : .
//--------------------------------------------------
double Utils::randDouble(double max)
{
	return (double(rand()) / double((RAND_MAX)) * max);
}





//--------------------------------------------------
//  choose : .
//--------------------------------------------------
double Utils::choose(double i, double j)
{
	if (randDouble(1) > 0.5) {
		return i;
	}
	return j;
}