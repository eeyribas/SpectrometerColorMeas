#ifndef SPECTRUMDATA_H
#define SPECTRUMDATA_H

#include <iostream>
#include <vector>
#include "utility.h"

class SpectrumData
{
public:
    SpectrumData();
    void ConvertString();
    void Clear();

    std::vector<std::pair<double, double>> spectrum;
    std::string spectrum_string;
};

#endif // SPECTRUMDATA_H
