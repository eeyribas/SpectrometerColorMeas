#include "datafilter.h"

std::vector<double> DataFilter::Selection(std::vector<double> main_data, int filter_type)
{
    std::vector<double> filter_data;
    if (filter_type == static_cast<int>(DataFilterType::kNormal))
        filter_data = Normal(main_data);
    else if (filter_type == static_cast<int>(DataFilterType::kMOA))
        filter_data = MOA(main_data);

    return filter_data;
}

std::vector<double> DataFilter::Normal(std::vector<double> main_data)
{
    std::vector<double> filter_data;
    for (uint i = 0; i < main_data.size(); i++)
        filter_data.push_back(main_data.at(i));

    return filter_data;
}

std::vector<double> DataFilter::MOA(std::vector<double> main_data)
{
    std::vector<double> filter_data;
    filter_data.push_back(main_data.at(0));
    filter_data.push_back(main_data.at(1));
    filter_data.push_back(main_data.at(2));
    filter_data.push_back(main_data.at(3));
    for (uint i = 4; i < main_data.size(); i++)
        filter_data.push_back((main_data.at(i - 4) + main_data.at(i - 3) + main_data.at(i - 2) + main_data.at(i - 1) + main_data.at(i)) / 5);

    return filter_data;
}
