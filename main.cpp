#include <QApplication>
#include "include/SmithChart/SmithChart.h"
#include "include/GeneralClasses/Admittance.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);
    SmithChart Chart(Impedance(100));

    Chart.drawAdmittance(Impedance(154));

    return App.exec();
}
