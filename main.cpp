#include <QApplication>
#include "include/SmithChart/SmithChart.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);
    SmithChart Chart;

    return App.exec();
}
