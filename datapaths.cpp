#include "datapaths.h"

DataPaths::DataPaths()
{
    Control();
}

void DataPaths::Control()
{
    if (!file_operations.Control(white_plate_values_path))
        file_operations.Create(white_plate_values_path);

    if (!file_operations.Control(grey_plate_values_path))
        file_operations.Create(grey_plate_values_path);
}
