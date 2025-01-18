#ifndef DATAPATHS_H
#define DATAPATHS_H

#include <iostream>
#include "fileoperations.h"

class DataPaths
{
public:
    DataPaths();
    void Control();

    std::string white_plate_values_path = "WhitePlate.txt";
    std::string grey_plate_values_path = "GreyPlate.txt";

private:
    FileOperations file_operations;
};

#endif // DATAPATHS_H
