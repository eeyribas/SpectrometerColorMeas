#include "spectrumdata.h"

SpectrumData::SpectrumData()
{
    Clear();
}

void SpectrumData::ConvertString()
{
    Utility utility;
    if (spectrum.size() > 0) {
        std::vector<double> tmp;
        for (uint i = 0; i < spectrum.size(); i++)
            tmp.push_back(spectrum.at(i).second);
        spectrum_string = utility.ConvertString(tmp);
    }
}

void SpectrumData::Clear()
{
    spectrum.clear();
    spectrum_string = "";
}
