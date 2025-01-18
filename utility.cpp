#include "utility.h"

std::string Utility::DateTimeNow()
{
    std::stringstream now_stream;
    time_t const now_time = time(nullptr);
    now_stream << std::put_time(localtime(&now_time), "%F %T");
    std::string now = now_stream.str();

    return now;
}

double Utility::Interpolation(double y_1, double y_0, double x, double x_1, double x_0)
{
    double y = ((y_0 * (x_1 - x)) + (y_1 * (x - x_0))) / (x_1 - x_0);

    return y;
}

double Utility::CheckUndefinedNumber(double value)
{
    double result = 0;
    if (std::isnan(value) || std::isinf(value))
        result = 0;
    else
        result = value;

    return result;
}

double Utility::CheckUndefinedNumber(double value, double digit)
{
    double result = CheckUndefinedNumber(value);
    result = Round(result, digit);

    return result;
}

double Utility::Round(double value, double digit)
{
    double tmp = round(value * pow(10, digit)) / pow(10, digit);

    return tmp;
}

std::string Utility::DecToHex(unsigned char n)
{
    int value = static_cast<int>(n);
    std::stringstream stream;
    stream << std::hex << value;
    std::string tmp = stream.str();

    return tmp;
}

std::string Utility::BoolToString(bool value)
{
    std::string tmp = "";
    if (value)
        tmp = "True";
    else
        tmp = "False";

    return tmp;
}

std::string Utility::ConvertString(std::vector<double> values)
{
    std::string tmp = "";
    if (values.size() > 0) {
        for (uint i = 0; i < values.size(); i++)
            tmp += std::to_string(Round(values.at(i), 4.0)) + " ";
    }

    return tmp;
}
