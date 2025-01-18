#ifndef XYZVALUES_H
#define XYZVALUES_H

#include <iostream>
#include <vector>
#include "standartvalues.h"

class XYZValues : public StandartValues
{
public:
    XYZValues();

    std::vector<double> x_degree;
    std::vector<double> y_degree;
    std::vector<double> z_degree;
};

#endif // XYZVALUES_H
