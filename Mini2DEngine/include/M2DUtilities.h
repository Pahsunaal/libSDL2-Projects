#ifndef M2D_UTILITIES_H
#define M2D_UTILITIES_H

/**
* @file Utilities.h
* @brief Provide several basic utilities to the engine
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <utility>
#include <cmath>
#include <fstream>
#include <rapidjson/document.h>

//--------------------------------------------------
//  Declarations
//--------------------------------------------------

namespace Utils
{
/** The mathematical constant of pi, to 20 decimal places */
constexpr double pi = 3.14159265358979323846;

/**
* Convert degrees to radians
* @param deg: the value in degrees to convert
*/
const double degToRad(double deg);

/**
* Convert a direction and length to a vector
* @param dir: direction in degrees
* @param length: the length of the target vector
*/
std::pair<double, double> dirLenToVector(double direction, double length);

/**
* Return a string of a files contents
* @param filename: path of the file to read from
*/
std::string* getStringFromFile(const char* filename);

/**
* Parse a json file into a Document object
* @param pathToFile: path of the file to read from
*/
rapidjson::Document* parseJSON(const char* pathToFile);

/**
* Get a random double between 0 and a maximum
* @param max: the maximum value of the double
*/
double randDouble(double max);

/**
* Choose between two options at random and return one of them
* @param i: the first option that could be picked
* @param j: the second option that could be picked
*/
double choose(double i, double j);
}

#endif // M2D_UTILITIES_H