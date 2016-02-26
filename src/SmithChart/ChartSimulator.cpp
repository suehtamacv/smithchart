#include "include/SmithChart/ChartSimulator.h"
#include <QHBoxLayout>
#include <QWidget>

ChartSimulator::ChartSimulator()
{
    setupInterface();
}

void ChartSimulator::setupInterface()
{
    setWindowTitle("Smith Chart Simulator");
    setMinimumSize(1000, 700);

    chart = std::make_shared<SmithChart>(Impedance(50), this);

    widgetLayout = std::make_shared<QHBoxLayout>(this);
    widgetLayout->addWidget(chart.get());
    setLayout(widgetLayout.get());

    show();
}
