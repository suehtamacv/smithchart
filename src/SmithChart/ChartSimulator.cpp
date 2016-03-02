#include "include/SmithChart/ChartSimulator.h"
#include "include/GeneralClasses/ImpedanceLineInput.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
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
    sidebarLayout = std::make_shared<QVBoxLayout>();

    widgetLayout->addWidget(chart.get());
    widgetLayout->addStretch();
    widgetLayout->addLayout(sidebarLayout.get());
    setLayout(widgetLayout.get());

    setSidebar();

    show();
}

void ChartSimulator::setSidebar()
{
    characteristicImpedance = std::make_shared<ImpedanceLineInput>();
    connect(characteristicImpedance.get(), SIGNAL(valueChanged(Impedance)),
            chart.get(), SLOT(setCharacteristicImpedance(Impedance&)));
    sidebarLayout->addWidget(new QLabel("Characteristic Impedance", this));
    sidebarLayout->addLayout(characteristicImpedance.get());
    sidebarLayout->addStretch();
}
