#ifndef CHARTSIMULATOR_H
#define CHARTSIMULATOR_H

#include <QWidget>
#include "SmithChart.h"

class QHBoxLayout;

class ChartSimulator : public QWidget
{
public:
    ChartSimulator();

private:
    std::shared_ptr<SmithChart> chart;

    std::shared_ptr<QHBoxLayout> widgetLayout;

    void setupInterface();
};

#endif // CHARTSIMULATOR_H
