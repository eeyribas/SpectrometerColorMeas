#include "luminaryvalues.h"

LuminaryValues::LuminaryValues(int lum_type)
{
    lum_list.clear();

    if (lum_type == static_cast<int>(LuminaryType::kD65)) {
        lum_list = Copy(d_65);
        Wx = Wd_65_x;
        Wy = Wd_65_y;
        Wz = Wd_65_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kA)) {
        lum_list = Copy(A_Light);
        Wx = WA_x;
        Wy = WA_y;
        Wz = WA_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kC)) {
        lum_list = Copy(C_Light);
        Wx = WC_x;
        Wy = WC_y;
        Wz = WC_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kD50)) {
        lum_list = Copy(d_50);
        Wx = Wd_50_x;
        Wy = Wd_50_y;
        Wz = Wd_50_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kD55)) {
        lum_list = Copy(d_55);
        Wx = Wd_55_x;
        Wy = Wd_55_y;
        Wz = Wd_55_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kD75)) {
        lum_list = Copy(d_75);
        Wx = Wd_75_x;
        Wy = Wd_75_y;
        Wz = Wd_75_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kF2)) {
        lum_list = Copy(F_2);
        Wx = Wf_2_x;
        Wy = Wf_2_y;
        Wz = Wf_2_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kF7)) {
        lum_list = Copy(F_7);
        Wx = Wf_7_x;
        Wy = Wf_7_y;
        Wz = Wf_7_z;
    } else if(lum_type == static_cast<int>(LuminaryType::kF11)) {
        lum_list = Copy(F_11);
        Wx = Wf_11_x;
        Wy = Wf_11_y;
        Wz = Wf_11_z;
    }
}

std::vector<double> LuminaryValues::Copy(std::vector<double> tmp_lum_list)
{
    std::vector<double> values;

    if (tmp_lum_list.size() > 0) {
        for (uint i = 0; i < tmp_lum_list.size(); i++)
            values.push_back(tmp_lum_list.at(i));
    }

    return values;
}
