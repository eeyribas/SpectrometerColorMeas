#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <vector>
#include <cmath>

class Utility
{
public:
    std::string DateTimeNow();
    double Interpolation(double y_1, double y_0, double x, double x_1, double x_0);
    double CheckUndefinedNumber(double value);
    double CheckUndefinedNumber(double value, double digit);
    double Round(double value, double digit);
    std::string DecToHex(unsigned char n);
    std::string BoolToString(bool value);
    std::string ConvertString(std::vector<double> values);
};

#endif // UTILITY_H
