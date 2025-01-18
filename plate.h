#ifndef PLATE_H
#define PLATE_H

#include <iostream>
#include <vector>
#include "datapaths.h"

class Plate : public DataPaths
{
public:
    void Read();
    std::vector<std::string> Read(std::string file_path);
    void Write(bool state, std::string white_values, std::string grey_values);
    void Write(std::string file_path, std::string values);

    std::vector<double> white_values;
    std::vector<double> grey_values;
    uint plate_values_count = 81;

private:
    FileOperations file_operations;
};

#endif // PLATE_H
