#include "spectrometerdata.h"

SpectrometerData::SpectrometerData()
{
    Clear();
}

void SpectrometerData::DarkData(SpectrumData tmp_spectrum_data)
{
    Clear();
    CopyToSpectrumData(tmp_spectrum_data);
}

void SpectrometerData::PlateData(SpectrumData tmp_spectrum_data, std::vector<double> plate_values)
{
    Clear();
    CopyToSpectrumData(tmp_spectrum_data);
    I0_plate = I0PlateCalc(spectrum_data.spectrum, plate_values);
}

void SpectrometerData::ReferenceData(SpectrumData tmp_spectrum_data, uint first_nm, uint default_first_nm, uint last_nm, double lamda, int tmp_meas_lum_type, int tmp_wity_lum_type, std::vector<std::pair<double, double>> tmp_I0_plate)
{
    Clear();
    meas_luminary_type = tmp_meas_lum_type;
    wity_luminary_type = tmp_wity_lum_type;
    CopyToSpectrumData(tmp_spectrum_data);
    I0_plate = tmp_I0_plate;

    Utility utility;
    XYZValues xyz_values;
    LuminaryValues meas_lum_values(meas_luminary_type);

    reflectance_values = ReflectanceCalc(spectrum_data.spectrum, I0_plate);

    x_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.x_degree, xyz_values.y_degree, lamda), 2.0);
    y_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.y_degree, xyz_values.y_degree, lamda), 2.0);
    z_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.z_degree, xyz_values.y_degree, lamda), 2.0);

    double QX_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.x_degree, xyz_values.y_degree, lamda, meas_lum_values.Wx);
    double QY_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.y_degree, xyz_values.y_degree, lamda, meas_lum_values.Wy);
    double QZ_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.z_degree, xyz_values.y_degree, lamda, meas_lum_values.Wz);
    L_value = utility.CheckUndefinedNumber((116 * QY_value) - 16, 2.0);
    a_value = utility.CheckUndefinedNumber(500 * (QX_value - QY_value), 2.0);
    b_value = utility.CheckUndefinedNumber(200 * (QY_value - QZ_value), 2.0);

    berger = BergerCalc(x_value, y_value, z_value);
    whiteness = WhitenessCalc(x_value, y_value, z_value);
    tint = TintCalc(x_value, y_value, z_value);
    yellowness = YellownessCalc(x_value, y_value, z_value);

    std::vector<int> rgb_values = RGBCalc(x_value, y_value, z_value);
    red = rgb_values.at(0);
    green = rgb_values.at(1);
    blue = rgb_values.at(2);

    hue = Hue(a_value, b_value);
    chroma = Chroma(a_value, b_value);
}

void SpectrometerData::SampleData(SpectrumData tmp_spectrum_data, uint first_nm, uint default_first_nm, uint last_nm, double lamda, int tmp_meas_lum_type, int tmp_wity_lum_type, std::vector<std::pair<double, double>> tmp_I0_plate, double L_ref, double a_ref, double b_ref)
{
    Clear();
    meas_luminary_type = tmp_meas_lum_type;
    wity_luminary_type = tmp_wity_lum_type;
    CopyToSpectrumData(tmp_spectrum_data);
    I0_plate = tmp_I0_plate;

    Utility utility;
    XYZValues xyz_values;
    LuminaryValues meas_lum_values(tmp_meas_lum_type);

    reflectance_values = ReflectanceCalc(spectrum_data.spectrum, I0_plate);

    x_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.x_degree, xyz_values.y_degree, lamda), 2.0);
    y_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.y_degree, xyz_values.y_degree, lamda), 2.0);
    z_value = utility.Round(XYZCalc(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.z_degree, xyz_values.y_degree, lamda), 2.0);

    double QX_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.x_degree, xyz_values.y_degree, lamda, meas_lum_values.Wx);
    double QY_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.y_degree, xyz_values.y_degree, lamda, meas_lum_values.Wy);
    double QZ_value = QXYZi(reflectance_values, first_nm, default_first_nm, last_nm, meas_lum_values.lum_list, xyz_values.z_degree, xyz_values.y_degree, lamda, meas_lum_values.Wz);
    L_value = utility.CheckUndefinedNumber((116 * QY_value) - 16, 2.0);
    a_value = utility.CheckUndefinedNumber(500 * (QX_value - QY_value), 2.0);
    b_value = utility.CheckUndefinedNumber(200 * (QY_value - QZ_value), 2.0);

    berger = BergerCalc(x_value, y_value, z_value);
    whiteness = WhitenessCalc(x_value, y_value, z_value);
    tint = TintCalc(x_value, y_value, z_value);
    yellowness = YellownessCalc(x_value, y_value, z_value);

    std::vector<int> rgb_values = RGBCalc(x_value, y_value, z_value);
    red = rgb_values.at(0);
    green = rgb_values.at(1);
    blue = rgb_values.at(2);

    hue = utility.Round(Hue(a_value, b_value), 2.0);
    chroma = utility.Round(Chroma(a_value, b_value), 2.0);

    delta_hue = abs(DeltaHue(a_value, b_value, a_ref, b_ref));
    double ref_chroma = Chroma(a_ref, b_ref);
    delta_chroma = utility.Round(abs(DeltaChroma(chroma, ref_chroma)), 2.0);
    cie_delta_e = utility.Round(abs(CIEDeltaE(L_value, a_value, b_value, L_ref, a_ref, b_ref)), 2.0);
    cmc_delta_e = utility.Round(abs(CMCDeltaE(2, 1, L_value, a_value, b_value, L_ref, a_ref, b_ref)), 2.0);
}

void SpectrometerData::CopyToSpectrumData(SpectrumData tmp_spectrum_data)
{
    if (tmp_spectrum_data.spectrum.size() > 0) {
        spectrum_data.Clear();

        for (uint i = 0; i < tmp_spectrum_data.spectrum.size(); i++)
            spectrum_data.spectrum.push_back(tmp_spectrum_data.spectrum.at(i));
        spectrum_data.spectrum_string = tmp_spectrum_data.spectrum_string;
    }
}

std::string SpectrometerData::ConvertString()
{
    Utility utility;

    std::string data = "x=" + std::to_string(utility.Round(x_value, 4.0)) + " ";
    data += "y=" + std::to_string(utility.Round(y_value, 4.0)) + " ";
    data += "z=" + std::to_string(utility.Round(z_value, 4.0)) + " ";

    data += "L=" + std::to_string(utility.Round(L_value, 4.0)) + " ";
    data += "a=" + std::to_string(utility.Round(a_value, 4.0)) + " ";
    data += "b=" + std::to_string(utility.Round(b_value, 4.0)) + " ";

    data += "Berger=" + std::to_string(utility.Round(berger, 4.0)) + " ";
    data += "Whiteness=" + std::to_string(utility.Round(whiteness, 4.0)) + " ";
    data += "Tint=" + std::to_string(utility.Round(tint, 4.0)) + " ";
    data += "Yellowness=" + std::to_string(utility.Round(yellowness, 4.0)) + " ";

    data += "Red=" + std::to_string(red) + " ";
    data += "Green=" + std::to_string(green) + " ";
    data += "Blue=" + std::to_string(blue) + " ";

    data += "hue=" + std::to_string(utility.Round(hue, 4.0)) + " ";
    data += "chroma=" + std::to_string(utility.Round(chroma, 4.0)) + " ";

    data += "DeltaHue=" + std::to_string(utility.Round(delta_hue, 4.0)) + " ";
    data += "DeltaChroma=" + std::to_string(utility.Round(delta_chroma, 4.0)) + " ";
    data += "CIEDeltaE=" + std::to_string(utility.Round(cie_delta_e, 4.0)) + " ";
    data += "CMCDeltaE=" + std::to_string(utility.Round(cmc_delta_e, 4.0)) + " ";

    spectrum_data.ConvertString();
    data += spectrum_data.spectrum_string;

    return data;
}

void SpectrometerData::Clear()
{
    meas_luminary_type = -1;
    wity_luminary_type = -1;
    spectrum_data.Clear();
    I0_plate.clear();
    reflectance_values.clear();
    x_value = 0;
    y_value = 0;
    z_value = 0;
    L_value = 0;
    a_value = 0;
    b_value = 0;
    berger = 0;
    whiteness = 0;
    tint = 0;
    yellowness = 0;
    red = 0;
    green = 0;
    blue = 0;
    hue = 0;
    chroma = 0;
    delta_hue = 0;
    delta_chroma = 0;
    cie_delta_e = 0;
    cmc_delta_e = 0;
}
