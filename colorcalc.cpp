#include "colorcalc.h"

double ColorCalc::CMCDeltaE(double l, double c, double L_sample, double a_sample, double b_sample, double L_ref, double a_ref, double b_ref)
{
    double delta_l = L_sample - L_ref;
    double delta_c = DeltaChroma(Chroma(a_sample, b_sample), Chroma(a_ref, b_ref));
    double tmp_c = Chroma(a_ref, b_ref);
    double Sc = (0.0638 * tmp_c / (1 + (0.0131 * tmp_c))) + 0.638;
    double h_value = Hue(a_ref, b_ref);
    double delta_h = DeltaHue(a_sample, b_sample, a_ref, b_ref);

    double SL = 0;
    if (L_ref >= 16)
        SL = (0.040975 * L_ref) / (1 + (0.01765 * L_ref));
    else
        SL = 0.511;

    double h_radyan = h_value * M_PI / 180;
    double T_value = 0;
    if (h_radyan > (164 * M_PI / 180) && h_radyan < (3 * M_PI / 180))
        T_value = 0.56 + abs(0.2 * cos(h_radyan + (168 * M_PI / 180)));
    else
        T_value = 0.36 + abs(0.4 * cos(h_radyan + (35 * M_PI / 180)));

    double f_value = sqrt(pow(sqrt(pow(a_ref, 2) + pow(b_ref, 2)), 4) / (1900 + pow(sqrt(pow(a_ref, 2) + pow(b_ref, 2)), 4)));
    double SH = Sc * ((T_value * f_value) + 1 - f_value);

    Utility utility;
    double delta_e = sqrt((pow(delta_l / (l * SL), 2)) + (pow(delta_c / (c * Sc), 2)) + (pow(delta_h / SH, 2)));
    delta_e = round(delta_e * 100000) / 100000;
    delta_e = utility.CheckUndefinedNumber(delta_e);

    return delta_e;
}

double ColorCalc::CIEDeltaE(double L_sample, double a_sample, double b_sample, double L_ref, double a_ref, double b_ref)
{
    Utility utility;
    double value_pow = pow((L_sample - L_ref), 2) + pow((a_sample - a_ref), 2) + pow((b_sample - b_ref), 2);
    double delta_e = sqrt(value_pow);
    delta_e = round(delta_e * 100000) / 100000;
    delta_e = utility.CheckUndefinedNumber(delta_e);

    return delta_e;
}

double ColorCalc::DeltaChroma(double sample, double ref)
{
    return (sample - ref);
}

double ColorCalc::Chroma(double a_value, double b_value)
{
    return (sqrt(pow(a_value, 2) + pow(b_value, 2)));
}

double ColorCalc::DeltaHue(double a_sample, double b_sample, double a_ref, double b_ref)
{
    Utility utility;
    double s_value = 0;
    if ((a_ref * b_sample) > (a_sample * b_ref))
        s_value = 1;
    else
        s_value = -1;

    double delta_h = s_value * sqrt(2 * ((sqrt(pow(a_sample, 2) + pow(b_sample, 2)) * sqrt(pow(a_ref, 2) + pow(b_ref, 2))) - (a_sample * a_ref) - (b_sample * b_ref)));
    delta_h = utility.CheckUndefinedNumber(delta_h);

    return delta_h;
}

double ColorCalc::Hue(double a_value, double b_value)
{
    Utility utility;
    double h_value = 0;
    double sign_value = 0;
    if (b_value == 0.0) {
        if (a_value > 0)
            sign_value = 1;
        else if(a_value == 0.0)
            sign_value = 0;
        else
            sign_value = -1;

        h_value = 90 * sign_value * (sign_value - 1);

    } else {
        if (b_value > 0)
            sign_value = 1;
        else if(b_value == 0.0)
            sign_value = 0;
        else
            sign_value = -1;

        h_value = 180 - ((180 / M_PI) * atan(a_value / b_value)) - (90 * sign_value);
    }

    h_value = utility.CheckUndefinedNumber(h_value);

    return h_value;
}

double ColorCalc::BergerCalc(double x_value, double y_value, double z_value)
{
    Utility utility;
    double berger_value = y_value + (3.108 * z_value) - (3.831 * x_value);
    berger_value = utility.CheckUndefinedNumber(berger_value);

    return berger_value;
}

double ColorCalc::WhitenessCalc(double x_value, double y_value, double z_value)
{
    Utility utility;
    double xyz_sum = x_value + y_value + z_value;
    double x_10 = x_value / xyz_sum;
    double y_10 = y_value / xyz_sum;
    double WI = y_value + (800 * (0.3138 - x_10)) + (1700 * (0.3310 - y_10));
    WI = utility.CheckUndefinedNumber(WI);

    return WI;
}

double ColorCalc::TintCalc(double x_value, double y_value, double z_value)
{
    Utility utility;
    double xyz_sum = x_value + y_value + z_value;
    double x_10 = x_value / xyz_sum;
    double y_10 = y_value / xyz_sum;
    double tint = (900 * (0.3138 - x_10)) - (650 * (0.3310 - y_10));
    tint = utility.CheckUndefinedNumber(tint);

    return tint;
}

double ColorCalc::YellownessCalc(double x_value, double y_value, double z_value)
{
    Utility utility;
    double YI = (100 * ((1.3013 * x_value) - (1.1498 * z_value))) / y_value;
    YI = utility.CheckUndefinedNumber(YI);

    return YI;
}

std::vector<int> ColorCalc::RGBCalc(double x_value, double y_value, double z_value)
{
    std::vector<int> rgb_values;
    std::vector<double> rgb;
    std::vector<double> t_rgb;
    std::vector<double> xyz;
    std::vector<double> col;
    col.push_back(x_value);
    col.push_back(y_value);
    col.push_back(z_value);
    for (uint i = 0; i < col.size(); i++)
        xyz.push_back(col.at(i) / 100.0);

    rgb.push_back((xyz.at(0) * 3.240479) + (xyz.at(1) * -1.537150) + (xyz.at(2) * -0.498535));
    rgb.push_back((xyz.at(0) * -0.969256) + (xyz.at(1) * 1.875992) + (xyz.at(2) * 0.041556));
    rgb.push_back((xyz.at(0) * 0.055648) + (xyz.at(1) * -0.204043) + (xyz.at(2) * 1.057311));

    for (uint i = 0; i < rgb.size(); i++) {
        if (rgb.at(i) > 0.0031308)
            t_rgb.push_back((1.055 * pow(rgb.at(i), (1.0 / 2.4))) - 0.055);
        else
            t_rgb.push_back(rgb.at(i) * 12.92);
    }

    double rgb_1 = t_rgb.at(0) * 255.0;
    double rgb_2 = t_rgb.at(1) * 255.0;
    double rgb_3 = t_rgb.at(2) * 255.0;

    int t_rgb_1 = static_cast<int>(round(rgb_1));
    int t_rgb_2 = static_cast<int>(round(rgb_2));
    int t_rgb_3 = static_cast<int>(round(rgb_3));

    if (t_rgb_1 > 255)
        t_rgb_1 = 255;
    else if (t_rgb_1 < 0)
        t_rgb_1 = 0;

    if (t_rgb_2 > 255)
        t_rgb_2 = 255;
    else if (t_rgb_2 < 0)
        t_rgb_2 = 0;

    if (t_rgb_3 > 255)
        t_rgb_3 = 255;
    else if (t_rgb_3 < 0)
        t_rgb_3 = 0;

    rgb_values.push_back(t_rgb_1);
    rgb_values.push_back(t_rgb_2);
    rgb_values.push_back(t_rgb_3);

    return rgb_values;
}

double ColorCalc::QXYZi(std::vector<double> reflectance_list, uint first_nm, uint default_first_nm, uint last_nm, std::vector<double> dx, std::vector<double> a_10, std::vector<double> y_10, double lamda, double white_point)
{
    Utility utility;
    double qxyzi = 0;
    double xyz = XYZCalc(reflectance_list, first_nm, default_first_nm, last_nm, dx, a_10, y_10, lamda);
    double qxyz = utility.CheckUndefinedNumber(xyz / white_point);
    if (qxyz > pow((6.0 / 29.0), 3.0))
        qxyzi = pow(qxyz, (1.0 / 3.0));
    else
        qxyzi = ((841.0 / 108.0) * qxyz) + (4.0 / 29.0);

    return qxyzi;
}

double ColorCalc::XYZCalc(std::vector<double> reflectance_list, uint first_nm, uint default_first_nm, uint last_nm, std::vector<double> dx, std::vector<double> a_10, std::vector<double> y_10, double lamda)
{
    Utility utility;
    double xyz_value = 0;
    double xyz = 0;

    uint first_nm_value = (first_nm - default_first_nm) / static_cast<uint>(lamda);
    uint last_nm_value = (last_nm - default_first_nm) / static_cast<uint>(lamda);
    for (uint i = first_nm_value; i <= last_nm_value; i++)
        xyz = xyz + (reflectance_list.at(i) * dx.at(i) * a_10.at(i) * lamda);

    xyz_value = KFactor(first_nm_value, last_nm_value, dx, y_10, lamda) * xyz;
    xyz_value = utility.CheckUndefinedNumber(xyz_value);

    return xyz_value;
}

double ColorCalc::KFactor(uint first_nm_count, uint last_nm_count, std::vector<double> dx, std::vector<double> y_10, double lamda)
{
    double K_sum = 0;
    for (uint i = first_nm_count; i <= last_nm_count; i++)
        K_sum = K_sum + (dx.at(i) * y_10.at(i) * lamda);
    double K_value = 100 / K_sum;

    return K_value;
}

std::vector<double> ColorCalc::ReflectanceCalc(std::vector<std::pair<double, double>> spectrum, std::vector<std::pair<double, double>> I0_plate)
{
    std::vector<double> reflectance_list;
    if (spectrum.size() > 0) {
        Utility utility;
        for (uint i = 0; i < spectrum.size(); i++)
            reflectance_list.push_back(utility.CheckUndefinedNumber(spectrum.at(i).second / I0_plate.at(i).second));
    }

    return reflectance_list;
}

std::vector<std::pair<double, double>> ColorCalc::I0PlateCalc(std::vector<std::pair<double, double>> spectrum, std::vector<double> plate_values)
{
    std::vector<std::pair<double, double>> I0_plate;
    if (spectrum.size() > 0) {
        Utility utility;
        for (uint i = 0; i < spectrum.size(); i++)
            I0_plate.push_back(std::pair<double, double>(spectrum.at(i).first, utility.CheckUndefinedNumber(spectrum.at(i).second / plate_values.at(i))));
    }

    return I0_plate;
}

