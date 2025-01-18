#ifndef COLORCALC_H
#define COLORCALC_H

#include <iostream>
#include <vector>
#include <cmath>
#include "utility.h"

class ColorCalc
{
public:
    double CMCDeltaE(double l, double c, double L_sample, double a_sample, double b_sample, double L_ref, double a_ref, double b_ref);
    double CIEDeltaE(double L_sample, double a_sample, double b_sample, double L_ref, double a_ref, double b_ref);
    double DeltaChroma(double sample, double ref);
    double Chroma(double a_value, double b_value);
    double DeltaHue(double a_sample, double b_sample, double a_ref, double b_ref);
    double Hue(double a_value, double b_value);
    double BergerCalc(double x_value, double y_value, double z_value);
    double WhitenessCalc(double x_value, double y_value, double z_value);
    double TintCalc(double x_value, double y_value, double z_value);
    double YellownessCalc(double x_value, double y_value, double z_value);
    std::vector<int> RGBCalc(double x_value, double y_value, double z_value);
    double QXYZi(std::vector<double> reflectance_list, uint first_nm, uint default_first_nm, uint last_nm, std::vector<double> dx, std::vector<double> a_10, std::vector<double> y_10, double lamda, double white_point);
    double XYZCalc(std::vector<double> reflectance_list, uint first_nm, uint default_first_nm, uint last_nm, std::vector<double> dx, std::vector<double> a_10, std::vector<double> y_10, double lamda);
    std::vector<double> ReflectanceCalc(std::vector<std::pair<double, double>> spectrum, std::vector<std::pair<double, double>> I0_plate);
    std::vector<std::pair<double, double>> I0PlateCalc(std::vector<std::pair<double, double>> spectrum, std::vector<double> plate_values);

private:
    double KFactor(uint first_nm_count, uint last_nm_count, std::vector<double> dx, std::vector<double> y_10, double lamda);
};

#endif // COLORCALC_H
