#include "xyzvalues.h"

XYZValues::XYZValues()
{
    x_degree.clear();
    y_degree.clear();
    z_degree.clear();

    for (uint i = 0; i < x_10.size(); i++) {
        x_degree.push_back(x_10.at(i));
        y_degree.push_back(y_10.at(i));
        z_degree.push_back(z_10.at(i));
    }
}
