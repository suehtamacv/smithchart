#ifndef CHARTSIMULATOR_H
#define CHARTSIMULATOR_H

#include <QMainWindow>
#include "SmithChart.h"

class ChartSimulator : public QMainWindow
{
public:
    ChartSimulator();

private:
    std::shared_ptr<SmithChart> chart;
    void setupInterface();
};

#endif // CHARTSIMULATOR_H
