#ifndef SPECTROMETERDATA_H
#define SPECTROMETERDATA_H

#include <iostream>
#include <vector>
#include <cmath>
#include "colorcalc.h"
#include "spectrumdata.h"
#include "xyzvalues.h"
#include "luminaryvalues.h"

class SpectrometerData : public ColorCalc
{
public:
    SpectrometerData();
    void DarkData(SpectrumData tmp_spectrum_data);
    void PlateData(SpectrumData tmp_spectrum_data, std::vector<double> plate_values);
    void ReferenceData(SpectrumData tmp_spectrum_data, uint first_nm, uint default_first_nm, uint last_nm, double lamda, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> tmp_I0_plate);
    void SampleData(SpectrumData tmp_spectrum_data, uint first_nm, uint default_first_nm, uint last_nm, double lamda, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> tmp_I0_plate, double L_ref, double a_ref, double b_ref);

    void CopyToSpectrumData(SpectrumData tmp_spectrum_data);
    std::string ConvertString();
    void Clear();

    int meas_luminary_type = -1;
    int wity_luminary_type = -1;
    SpectrumData spectrum_data;
    std::vector<std::pair<double, double>> I0_plate;
    std::vector<double> reflectance_values;
    double x_value = 0;
    double y_value = 0;
    double z_value = 0;
    double L_value = 0;
    double a_value = 0;
    double b_value = 0;
    double berger;
    double whiteness;
    double tint;
    double yellowness;
    int red;
    int green;
    int blue;
    double hue = 0;
    double chroma = 0;
    double delta_hue = 0;
    double delta_chroma = 0;
    double cie_delta_e = 0;
    double cmc_delta_e = 0;

    uint meas_data_length = 81;
};

#endif // SPECTROMETERDATA_H
