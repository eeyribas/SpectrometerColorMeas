#include "plate.h"

void Plate::Read()
{
    white_values.clear();
    std::vector<std::string> tmp_white_values = Read(white_plate_values_path);
    if (tmp_white_values.size() == plate_values_count) {
        for (uint i = 0; i < tmp_white_values.size(); i++)
            white_values.push_back(std::stod(tmp_white_values.at(i)));
    }

    grey_values.clear();
    std::vector<std::string> tmp_grey_values = Read(grey_plate_values_path);
    if (tmp_grey_values.size() == plate_values_count) {
        for (uint i = 0; i < tmp_grey_values.size(); i++)
            grey_values.push_back(std::stod(tmp_grey_values.at(i)));
    }
}

std::vector<std::string> Plate::Read(std::string file_path)
{
    std::vector<std::string> values = file_operations.Read(file_path);

    return values;
}

void Plate::Write(bool state, std::string t_white_values, std::string t_grey_values)
{
    state = true;
    Write(white_plate_values_path, t_white_values);
    Write(grey_plate_values_path, t_grey_values);
}

void Plate::Write(std::string file_path, std::string values)
{
    file_operations.Remove(file_path);
    if (!file_operations.Control(file_path)) {
        file_operations.Create(file_path);
        file_operations.Write(file_path, values);
    }
}
