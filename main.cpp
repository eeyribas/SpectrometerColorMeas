#include <QCoreApplication>
#include "plate.h"
#include "spectrometermodel.h"
#include "insion.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Plate plate;
    plate.Read();

    SpectrometerModel *spec_model = new insion();
    spec_model->SetBaudRate(3000000);
    spec_model->SetDataLength(81);
    spec_model->SetDefaultFirstNm(380);
    spec_model->SetDefaultLastNm(780);
    spec_model->SetLamda(5);

    SpectrometerData dark_spec_data = spec_model->Dark(10, 5, 1, 5);
    SpectrometerData plate_spec_data = spec_model->Plate(10, 5, 1, 5, plate.white_values);
    SpectrometerData reference_spec_data = spec_model->Reference(10, 5, 1, 5, 400, 700, 0, 0, plate_spec_data.I0_plate);
    SpectrometerData sample_spec_data = spec_model->Sample(10, 5, 1, 5, 400, 700, 0, 0, plate_spec_data.I0_plate,
                                        reference_spec_data.L_value, reference_spec_data.a_value, reference_spec_data.b_value);

    return a.exec();
}
