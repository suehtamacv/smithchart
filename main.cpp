#include <QApplication>
#include "include/SmithChart/SmithChart.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);
    SmithChart Chart(Impedance(100));

    return App.exec();
}
