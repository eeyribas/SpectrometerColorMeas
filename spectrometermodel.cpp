#include "spectrometermodel.h"

SpectrometerModel::~SpectrometerModel() {   }

void SpectrometerModel::SetPortName(std::string value) {    port_name = value;  }
std::string SpectrometerModel::GetPortName() {  return port_name;   }
void SpectrometerModel::SetBaudRate(int value) {    baud_rate = value;  }
int SpectrometerModel::GetBaudRate() {  return baud_rate;   }
void SpectrometerModel::SetDataLength(uint value) {  data_length = value;    }
uint SpectrometerModel::GetDataLength() {    return data_length; }
void SpectrometerModel::SetDefaultFirstNm(uint value) {  default_first_nm = value;    }
uint SpectrometerModel::GetDefaultFirstNm() {    return default_first_nm;     }
void SpectrometerModel::SetDefaultLastNm(uint value) {   default_last_nm = value;     }
uint SpectrometerModel::GetDefaultLastNm() { return default_last_nm; }
void SpectrometerModel::SetLamda(double value) {    lamda = value; }
double SpectrometerModel::GetLamda() {  return lamda;   }
