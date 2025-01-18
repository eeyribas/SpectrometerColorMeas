#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <iostream>
#include <vector>

enum DataFilterType
{
    kNormal = 0,
    kMOA = 1
};

class DataFilter
{
public:
    std::vector<double> Selection(std::vector<double> main_data, int filter_type);

private:
    std::vector<double> Normal(std::vector<double> main_data);
    std::vector<double> MOA(std::vector<double> main_data);
};

#endif // DATAFILTER_H
