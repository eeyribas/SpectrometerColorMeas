#ifndef SPECTROMETERMODEL_H
#define SPECTROMETERMODEL_H

#include <iostream>
#include "spectrometerdata.h"

class SpectrometerModel
{
public:
    virtual ~SpectrometerModel() = 0;
    virtual bool Open() = 0;
    virtual bool IsOpen() = 0;
    virtual void Close() = 0;
    virtual bool Control(std::string serial_number, double analog_gain, int digital_gain) = 0;
    virtual std::string SerialNumber() = 0;
    virtual bool AnalogGain(double analog_gain) = 0;
    virtual bool DigitalGain(int digital_gain) = 0;
    virtual void NmValuesCalc() = 0;
    virtual SpectrometerData Dark(double int_time, int av_scan, int filter_type, int loop) = 0;
    virtual SpectrometerData Plate(double int_time, int av_scan, int filter_type, int loop, std::vector<double> plate_values) = 0;
    virtual SpectrometerData Reference(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate) = 0;
    virtual SpectrometerData Sample(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate, double L_ref, double a_ref, double b_ref) = 0;

    void SetPortName(std::string value);
    std::string GetPortName();
    void SetBaudRate(int value);
    int GetBaudRate();
    void SetDataLength(uint value);
    uint GetDataLength();
    void SetDefaultFirstNm(uint value);
    uint GetDefaultFirstNm();
    void SetDefaultLastNm(uint value);
    uint GetDefaultLastNm();
    void SetLamda(double value);
    double GetLamda();

private:
    std::string port_name;
    int baud_rate;
    uint data_length;
    uint default_first_nm;
    uint default_last_nm;
    double lamda;
};

#endif // SPECTROMETERMODEL_H
