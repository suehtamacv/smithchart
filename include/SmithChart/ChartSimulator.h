#ifndef CHARTSIMULATOR_H
#define CHARTSIMULATOR_H

#include <QWidget>
#include "SmithChart.h"

class QHBoxLayout;
class QVBoxLayout;
class ImpedanceLineInput;

class ChartSimulator : public QWidget
{
public:
    ChartSimulator();

private:
    std::shared_ptr<SmithChart> chart;

    std::shared_ptr<QHBoxLayout> widgetLayout;
    std::shared_ptr<QVBoxLayout> sidebarLayout;

    std::shared_ptr<ImpedanceLineInput> characteristicImpedance;

    void setupInterface();
    void setSidebar();
};

#endif // CHARTSIMULATOR_H
