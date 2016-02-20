#include "include/SmithChart/SmithChart.h"
#include "include/GeneralClasses/Impedance.h"
#include "include/GeneralClasses/Admittance.h"
#include <QLayout>

SmithChart::SmithChart(Impedance Z0, QWidget *parent) :
    QWidget(parent), characteristicImpedance(Z0), chartTransformation(Z0)
{
    setupInterface();
}

SmithChart::SmithChart(Admittance Y0, QWidget *parent) :
    SmithChart(Y0.toImpedance(), parent)
{

}

void SmithChart::setupInterface()
{
    //Window Title and Size
    setWindowTitle("Smith Chart");
    setMinimumSize(400, 400);

    //Window Background
    setAutoFillBackground(true);
    QPalette Palette(palette());
    Palette.setColor(QPalette::Background, Qt::white);
    setPalette(Palette);

    chart = std::make_shared<QLabel>(this);
    chartPicture = std::make_shared<QPicture>();
    chart->setContentsMargins(0, 0, 0, 0);
    chart->setPicture(*chartPicture);
    chart->setSizePolicy(QSizePolicy::MinimumExpanding,
                         QSizePolicy::MinimumExpanding);

    auto HLayout = new QHBoxLayout(this);
    HLayout->addWidget(chart.get(), 0, Qt::AlignCenter);
    HLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(HLayout);

    show();
}

void SmithChart::paintEvent(QPaintEvent *)
{
    auto painter = new QPainter(chartPicture.get());

    painter->translate(chart->rect().center());

    drawSmithChart(painter);
    drawImpedances(painter);

    delete painter;
}

void SmithChart::resizeEvent(QResizeEvent *)
{
    auto minSize = std::min(rect().height(), rect().width());
    chart->setMinimumSize(minSize, minSize);
    chartPicture->setBoundingRect(chart->rect());
}

void SmithChart::drawSmithChart(QPainter *painter)
{
    if (!painter)
        {
        return;
        }

    painter->setRenderHint(QPainter::Antialiasing, true);

    chartRadius = std::round(0.45 * std::min(
                                 chart->rect().height(), chart->rect().width()));

    painter->drawEllipse(QPoint(0, 0), chartRadius, chartRadius);
}

void SmithChart::drawImpedance(const Impedance &impedance)
{
    drawnImpedances.push_back(Impedance(impedance));
}

void SmithChart::drawAdmittance(const Admittance &admittance)
{
    drawImpedance(admittance.toImpedance());
}

void SmithChart::drawImpedances(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    for (auto &impedance : drawnImpedances)
        {
        auto z = chartTransformation.findPoint(impedance);
        z *= chartRadius;

        painter->drawPoint(QPoint(z.real(), z.imag()));
        }
}
