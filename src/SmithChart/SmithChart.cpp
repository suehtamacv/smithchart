#include "include/SmithChart/SmithChart.h"

SmithChart::SmithChart(QWidget *parent) : QWidget(parent)
{
    setupInterface();
}

void SmithChart::setupInterface()
{
    setWindowTitle("Smith Chart");
    setFixedSize(800, 600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    show();
}
