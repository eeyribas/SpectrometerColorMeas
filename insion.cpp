#include "insion.h"

bool insion::Open()
{
    bool state = serial_port.Open(GetPortName(), GetBaudRate());

    return state;
}

bool insion::IsOpen()
{
    bool state = serial_port.IsOpen();

    return state;
}

void insion::Close()
{
    serial_port.Close();
}

bool insion::Control(std::string serial_number, double analog_gain, int digital_gain)
{
    bool state = false;

    if (Open()) {
        if (SerialNumber() == serial_number) {

            if (AnalogGain(analog_gain) && DigitalGain(digital_gain)) {
                NmValuesCalc();
                state = true;
            } else {
                Close();
                state = false;
            }
        } else {
            Close();
            state = false;
        }
    } else {
        state = false;
    }

    return state;
}

std::string insion::SerialNumber()
{
    std::string serial_number = "";
    if (IsOpen()) {
        serial_port.Write(serial_number_code);
        std::vector<unsigned char> read_data = serial_port.Read(serial_number_dl);
        if (read_data.size() ==  serial_number_dl) {
            for (uint i = 0; i < read_data.size(); i++) {
                if (read_data.at(i) != finish_byte)
                    serial_number += std::to_string(read_data.at(i) - zero_char);
            }
        }
    }

    return serial_number;
}

bool insion::AnalogGain(double analog_gain)
{
    bool state = false;
    if (IsOpen()) {
        std::vector<char> tmp;
        for (uint i = 0; i < analog_gain_code.size(); i++)
            tmp.push_back(analog_gain_code.at(i));

        int first = (static_cast<int>(analog_gain)) + zero_char;
        int second = (static_cast<int>(analog_gain * 10) % 10) + zero_char;
        tmp.push_back(static_cast<char>(first));
        tmp.push_back('.');
        tmp.push_back(static_cast<char>(second));
        tmp.push_back('\r');

        serial_port.Write(tmp);
        std::vector<unsigned char> read_data = serial_port.Read(analog_gain_dl);
        if (read_data.size() == analog_gain_dl && read_data.at(0) == accuracy_digital_and_analog)
            state = true;
    }

    return state;
}

bool insion::DigitalGain(int digital_gain)
{
    bool state = false;
    if (IsOpen()) {
        std::vector<char> tmp;
        for (uint i = 0; i < digital_gain_code.size(); i++)
            tmp.push_back(digital_gain_code.at(i));

        tmp.push_back(static_cast<char>(digital_gain + zero_char));
        tmp.push_back('\r');

        serial_port.Write(tmp);
        std::vector<unsigned char> read_data = serial_port.Read(digital_gain_dl);
        if (read_data.size() == digital_gain_dl && read_data.at(0) == accuracy_digital_and_analog)
            state = true;
    }

    return state;
}

void insion::NmValuesCalc()
{
    double a_factor = NmPolynomialFactor(4);
    double b_factor = NmPolynomialFactor(3);
    double c_factor = NmPolynomialFactor(2);
    double d_factor = NmPolynomialFactor(1);
    double e_factor = NmPolynomialFactor(0);

    nm_values.clear();
    double mux = 0;
    for (uint i = 0; i < pixel_dl; i++) {
        mux = static_cast<double>(i);
        nm_values.push_back((a_factor * pow(mux, 4)) + (b_factor * pow(mux, 3)) + (c_factor * pow(mux, 2)) + (d_factor * pow(mux, 1)) + (e_factor * pow(mux, 0)));
    }

    choose_nm_indexs.clear();
    double search_number = 2;
    uint m = 0, n = 0;
    while (m < pixel_dl && n < GetDataLength()) {
        search_number = abs(nm_values.at(m) - static_cast<double>(GetDefaultFirstNm() + (n * 5)));
        if (search_number >= 0 && search_number < 2) {
            choose_nm_indexs.push_back(static_cast<int>(m));
            m = 0;
            n++;
        } else {
            m++;
        }
    }
}

double insion::NmPolynomialFactor(int factor)
{
    double result = 0;
    std::vector<char> tmp;
    for (uint i = 0; i < fit_code.size(); i++)
        tmp.push_back(fit_code.at(i));

    tmp.push_back(static_cast<char>(factor + zero_char));
    tmp.push_back('?');
    tmp.push_back('\r');

    serial_port.Write(tmp);
    std::vector<unsigned char> read_data = serial_port.Read(nm_poly_factor_dl, finish_byte);
    if (read_data.size() == nm_poly_factor_dl || read_data.size() == (nm_poly_factor_dl - 1)) {
        std::string value = "";
        for (uint i = 0; i < read_data.size(); i++)
            value += static_cast<char>(read_data.at(i));

        result = std::stod(value);
    }

    return result;
}

SpectrometerData insion::Dark(double int_time, int av_scan, int filter_type, int loop)
{
    SpectrometerData spectrometer_data;
    std::vector<char> tmp;
    for (uint i = 0; i < dark_code.size(); i++)
        tmp.push_back(dark_code.at(i));

    std::vector<char> int_time_array = ConvertIntTime(int_time);
    for (uint i = 0; i < int_time_array.size(); i++)
        tmp.push_back(int_time_array.at(i));

    std::string s_av_scan = std::to_string(av_scan);
    for (uint i = 0; i < s_av_scan.length(); i++)
        tmp.push_back(static_cast<char>(s_av_scan[i]));

    for (uint i = 0; i < last_code.size(); i++)
        tmp.push_back(last_code.at(i));

    SpectrumData spectrum_data = SpectrumCalc(tmp, filter_type, loop);
    spectrometer_data.DarkData(spectrum_data);

    return spectrometer_data;
}

SpectrometerData insion::Plate(double int_time, int av_scan, int filter_type, int loop, std::vector<double> plate_values)
{
    SpectrometerData spectrometer_data;
    std::vector<char> tmp;
    for (uint i = 0; i < refr_code.size(); i++)
        tmp.push_back(refr_code.at(i));

    std::vector<char> int_time_array = ConvertIntTime(int_time);
    for (uint i = 0; i < int_time_array.size(); i++)
        tmp.push_back(int_time_array.at(i));

    std::string s_av_scan = std::to_string(av_scan);
    for (uint i = 0; i < s_av_scan.length(); i++)
        tmp.push_back(static_cast<char>(s_av_scan[i]));

    for (uint i = 0; i < last_code.size(); i++)
        tmp.push_back(last_code.at(i));

    SpectrumData spectrum_data = SpectrumCalc(tmp, filter_type, loop);
    spectrometer_data.PlateData(spectrum_data, plate_values);

    return spectrometer_data;
}

SpectrometerData insion::Reference(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate)
{
    SpectrometerData spectrometer_data;
    std::vector<char> tmp;
    for (uint i = 0; i < refr_code.size(); i++)
        tmp.push_back(refr_code.at(i));

    std::vector<char> int_time_array = ConvertIntTime(int_time);
    for (uint i = 0; i < int_time_array.size(); i++)
        tmp.push_back(int_time_array.at(i));

    std::string s_av_scan = std::to_string(av_scan);
    for (uint i = 0; i < s_av_scan.length(); i++)
        tmp.push_back(static_cast<char>(s_av_scan[i]));

    for (uint i = 0; i < last_code.size(); i++)
        tmp.push_back(last_code.at(i));

    SpectrumData spectrum_data = SpectrumCalc(tmp, filter_type, loop);
    spectrometer_data.ReferenceData(spectrum_data, first_nm, GetDefaultFirstNm(), last_nm, GetLamda(), meas_lum_type, wity_lum_type, I0_plate);

    return spectrometer_data;
}

SpectrometerData insion::Sample(double int_time, int av_scan, int filter_type, int loop, uint first_nm, uint last_nm, int meas_lum_type, int wity_lum_type, std::vector<std::pair<double, double>> I0_plate, double L_ref, double a_ref, double b_ref)
{
    SpectrometerData spectrometer_data;
    std::vector<char> tmp;
    for (uint i = 0; i < refr_code.size(); i++)
        tmp.push_back(refr_code.at(i));

    std::vector<char> int_time_array = ConvertIntTime(int_time);
    for (uint i = 0; i < int_time_array.size(); i++)
        tmp.push_back(int_time_array.at(i));

    std::string s_av_scan = std::to_string(av_scan);
    for (uint i = 0; i < s_av_scan.length(); i++)
        tmp.push_back(static_cast<char>(s_av_scan[i]));

    for (uint i = 0; i < last_code.size(); i++)
        tmp.push_back(last_code.at(i));

    SpectrumData spectrum_data = SpectrumCalc(tmp, filter_type, loop);
    spectrometer_data.SampleData(spectrum_data, first_nm, GetDefaultFirstNm(), last_nm, GetLamda(), meas_lum_type, wity_lum_type, I0_plate, L_ref, a_ref, b_ref);

    return spectrometer_data;
}

SpectrumData insion::SpectrumCalc(std::vector<char> write_data, int filter_type, int loop)
{
    SpectrumData spectrum_data;
    double *loop_signal_array = new double[meas_dl];
    for (uint i = 0; i < meas_dl; i++)
        loop_signal_array[i] = 0;

    for (int i = 0; i < loop; i++) {

        serial_port.Write(write_data);
        std::vector<unsigned char> read_data = serial_port.Read(meas_hex_dl);
        if (read_data.at(0) == meas_first_byte && read_data.size() == meas_hex_dl) {
            std::vector<double> all_signal = ConvertSignal(read_data);
            for (uint j = 0; j < meas_dl; j++)
                loop_signal_array[j] = loop_signal_array[j] + all_signal.at(j);
        }
    }

    std::vector<double> loop_signal_list;
    double d_loop = static_cast<double>(loop);
    for (uint i = 0; i < meas_dl; i++)
        loop_signal_list.push_back(loop_signal_array[i] / d_loop);
    delete[] loop_signal_array;

    DataFilter data_filter;
    std::vector<double> filter_signal_list = data_filter.Selection(loop_signal_list, filter_type);

    std::vector<std::pair<double, double>> selection_spectrum_list = SpectrumPixelSelection(filter_signal_list);

    if (selection_spectrum_list.size() > 0) {
        spectrum_data.spectrum.clear();
        for (uint i = 0; i < selection_spectrum_list.size(); i++)
            spectrum_data.spectrum.push_back(selection_spectrum_list.at(i));
    }

    spectrum_data.ConvertString();

    return spectrum_data;
}

std::vector<std::pair<double, double>> insion::SpectrumPixelSelection(std::vector<double> spectrum)
{
    Utility utility;
    std::vector<std::pair<double, double>> selection_spectrum;
    uint nm_selection = 0, nm_seq_selection = 0;
    uint tmp_data_length = GetDataLength();
    double tmp_first_nm = static_cast<double>(GetDefaultFirstNm());
    double tmp_lamda = static_cast<double>(GetLamda());

    if (spectrum.size() == meas_dl) {
        for (uint i = 0; i < tmp_data_length; i++) {
            nm_selection = static_cast<uint>(choose_nm_indexs.at(i));
            nm_seq_selection = static_cast<uint>(choose_nm_indexs.at(i) + 1);

            selection_spectrum.push_back(std::pair<double, double>(tmp_first_nm + (static_cast<double>(i) * tmp_lamda), utility.Interpolation(spectrum.at(nm_seq_selection), spectrum.at(nm_selection), tmp_first_nm + (static_cast<double>(i) * tmp_lamda), nm_values.at(nm_seq_selection), nm_values.at(nm_selection))));
        }
    }

    return selection_spectrum;
}

std::vector<double> insion::ConvertSignal(std::vector<unsigned char> read_data)
{
    Utility utility;
    std::vector<double> all_spectrum;
    std::vector<std::string> hex_values;

    if (read_data.size() == meas_hex_dl) {
        for (uint i = 0; i < read_data.size(); i++) {
            std::string data = utility.DecToHex(read_data.at(i));
            if (data.length() != 2)
                data = "0" + data;
            hex_values.push_back(data);
        }

        for (uint i = 0; i < hex_values.size(); i += 2) {
            std::string hex = hex_values.at(i) + hex_values.at(i + 1);
            int data = std::stoi(hex, 0, 16);
            all_spectrum.push_back(static_cast<double>(data));
        }
    }

    return all_spectrum;
}

std::vector<char> insion::ConvertIntTime(double int_time)
{
    double tmp_int_time = round(int_time * 10);
    int first_int_time = static_cast<int>(tmp_int_time) / 10;
    int last_int_time = static_cast<int>(tmp_int_time) % 10;
    std::string s_int_time = std::to_string(first_int_time);

    std::vector<char> tmp;
    for (uint i = 0; i < s_int_time.length(); i++)
        tmp.push_back(static_cast<char>(s_int_time[i]));
    tmp.push_back('.');
    tmp.push_back(static_cast<char>(last_int_time + zero_char));
    tmp.push_back(' ');

    return tmp;
}

