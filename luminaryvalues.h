#ifndef LUMINARYVALUES_H
#define LUMINARYVALUES_H

#include <iostream>
#include <vector>
#include "standartvalues.h"

enum LuminaryType
{
    kD65 = 0,
    kA = 1,
    kC = 2,
    kD50 = 3,
    kD55 = 4,
    kD75 = 5,
    kF2 = 6,
    kF7 = 7,
    kF11 = 8
};


class LuminaryValues : public StandartValues
{
public:
    LuminaryValues(int lum_type);
    std::vector<double> Copy(std::vector<double> tmp_lum_list);

    std::vector<double> lum_list;
    double Wx = 0;
    double Wy = 0;
    double Wz = 0;
};

#endif // LUMINARYVALUES_H
