#ifndef INSION_H
#define INSION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "spectrometermodel.h"
#include "serialport.h"
#include "datafilter.h"
#include "utility.h"

class insion : public SpectrometerModel
{
public:
    ~insion() { }
    bool Open();
    bool IsOpen();
    void Close();
    bool Control(std::string serial_number, double analog_gain, int digital_gain);
    std::string SerialNumber();
    bool AnalogGain(double analog_gain);
    bool DigitalGain(int digital_gain);
    void NmValuesCalc();
    SpectrometerData Dark(double int_time, int av_scan, int filter_type, int loop);
    SpectrometerData Plate(double int_time, int av_scan, int filter_type, int loop, std::vector<double> plate_values);
    SpectrometerData Reference(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate);
    SpectrometerData Sample(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate, double L_ref, double a_ref, double b_ref);

private:
    double NmPolynomialFactor(int factor);
    SpectrumData SpectrumCalc(std::vector<char> write_data, int filter_type, int loop);
    std::vector<std::pair<double, double>> SpectrumPixelSelection(std::vector<double> spectrum);
    std::vector<double> ConvertSignal(std::vector<unsigned char> read_data);
    std::vector<char> ConvertIntTime(double int_time);

    std::vector<char> serial_number_code = {'*', 'P', 'A', 'R', 'A', 'm', 'e', 't', 'e', 'r', ':', 'S', 'E', 'R', 'N', 'u', 'm', 'b', 'e', 'r', '?', '\r'};
    std::vector<char> analog_gain_code = {'*', 'P', 'A', 'R', 'A', 'm', 'e', 't', 'e', 'r', ':', 'G', 'A', 'I', 'N', ' '};
    std::vector<char> digital_gain_code = {'*', 'P', 'A', 'R', 'A', 'm', 'e', 't', 'e', 'r', ':', 'P', 'D', 'A', 'G', 'a', 'i', 'n', ' '};
    std::vector<char> fit_code = {'*', 'P', 'A', 'R', 'A', 'm', 'e', 't', 'e', 'r', ':', 'F', 'I', 'T'};
    std::vector<char> dark_code = {'*', 'M', 'E', 'A', 'S', 'u', 'r', 'e', ':', 'D', 'A', 'R', 'K', 's', 'p', 'e', 'c', 't', 'r', 'a', ' '};
    std::vector<char> refr_code = {'*', 'M', 'E', 'A', 'S', 'u', 'r', 'e', ':', 'R', 'E', 'F', 'E', 'R', 'e', 'n', 'c', 'e', ' '};
    std::vector<char> last_code = {' ', 'f', 'o', 'r', 'm', 'a', 't', '\r'};

    uint nm_poly_factor_dl = 14;
    uint serial_number_dl = 8;

    uint pixel_dl = 2048;
    uint meas_hex_dl = 4098;
    uint meas_dl = 2049;
    unsigned char meas_first_byte = 6;
    uint finish_byte = 13;

    uint analog_gain_dl = 1;
    uint digital_gain_dl = 1;
    unsigned char accuracy_digital_and_analog = 6;

    uint search_max_device = 10;
    int zero_char = 48;

    SerialPort serial_port;

    std::vector<double> nm_values;
    std::vector<int> choose_nm_indexs;
};

#endif // INSION_H
