#include "include/SmithChart/ChartSimulator.h"
#include <QHBoxLayout>

ChartSimulator::ChartSimulator()
{
    setupInterface();
}

void ChartSimulator::setupInterface()
{
    setWindowTitle("Smith Chart Simulator");
    setMinimumSize(1000, 700);

    chart = std::make_shared<SmithChart>(Impedance(50), this);

    show();
}
