#include <QApplication>
#include "include/SmithChart/ChartSimulator.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);
    ChartSimulator chart;

    return App.exec();
}
