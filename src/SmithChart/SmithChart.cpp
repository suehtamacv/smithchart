#include "include/SmithChart/SmithChart.h"

SmithChart::SmithChart(QWidget *parent) : QWidget(parent)
{
    setupInterface();
}

void SmithChart::setupInterface()
{
    //Window Title and Size
    setWindowTitle("Smith Chart");
    setFixedSize(600, 600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //Window Background
    setAutoFillBackground(true);
    QPalette Palette(palette());
    Palette.setColor(QPalette::Background, Qt::white);
    setPalette(Palette);

    show();
}

void SmithChart::paintEvent(QPaintEvent *)
{
    drawSmithChart();
}

void SmithChart::drawSmithChart()
{
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing, true);
    Painter.drawLine(0, 0, 1000, 1000);
}
