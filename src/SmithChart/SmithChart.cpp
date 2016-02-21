#include "include/SmithChart/SmithChart.h"
#include "include/GeneralClasses/Impedance.h"
#include "include/GeneralClasses/Admittance.h"
#include "include/GeneralClasses/Circle.h"
#include <algorithm>
#include <QLayout>

SmithChart::SmithChart(Impedance Z0, QWidget *parent) :
    QWidget(parent), characteristicImpedance(Z0), chartTransformation(Z0)
{
    setupInterface();
    povoateChartValues();
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

    chartRadius =
        std::round(0.45 * std::min(chart->rect().height(), chart->rect().width()));
    QPainterPath chartBoundary(chart->rect().center());
    chartBoundary.addEllipse(QPoint(0, 0), chartRadius, chartRadius);

    painter->drawPath(chartBoundary);
    painter->setClipPath(chartBoundary);

    for (auto pair : impedanceValues)
        {
        double r = pair.first / 100.0;
        painter->setClipPath(getImpedanceBoundary(pair.second).subtracted(
                                 getImpedanceBoundary(previousImpedance.at(pair.second))));

        auto circ = Circle(r / (r + 1.0), 1.0 / (r + 1.0)) * chartRadius;
        painter->drawEllipse(QPointF(circ.x(), circ.y()), circ.radius(), circ.radius());
        }

    for (auto pair : impedanceValues)
        {
        double x = pair.first / 100.0;
        painter->setClipPath(getImpedanceBoundary(pair.second).subtracted(
                                 getImpedanceBoundary(previousImpedance.at(pair.second))));

        if (x == 0)
            {
            continue;
            }

        auto circ = Circle(complex(1, 1.0 / x), 1.0 / x) * chartRadius;
        painter->drawEllipse(QPointF(circ.x(), circ.y()), circ.radius(), circ.radius());
        circ = Circle(complex(1, - 1.0 / x), 1.0 / x) * chartRadius;
        painter->drawEllipse(QPointF(circ.x(), circ.y()), circ.radius(), circ.radius());
        }

    painter->setClipPath(chartBoundary);
    painter->drawLine(-chartRadius, 0, chartRadius, 0);
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

void SmithChart::povoateChartValues()
{
    impedanceValues.clear();
    previousImpedance.clear();

    previousImpedance = {{.2, -1}, {.5, .2}, {1, .5}, {2, 1}, {5, 2}, {10, 5}, {20, 10}, {50, 20}};

    for (long int var = 0; var <= 20; var += 1)
        {
        impedanceValues.emplace(var, 0.2);
        }
    for (long int var = 0; var <= 50; var += 2)
        {
        impedanceValues.emplace(var, 0.5);
        }
    for (long int var = 0; var <= 100; var += 5)
        {
        impedanceValues.emplace(var, 1.0);
        }
    for (long int var = 0; var <= 200; var += 10)
        {
        impedanceValues.emplace(var, 2.0);
        }
    for (long int var = 0; var <= 500; var += 20)
        {
        impedanceValues.emplace(var, 5.0);
        }
    for (long int var = 0; var <= 1000; var += 100)
        {
        impedanceValues.emplace(var, 10.0);
        }
    for (long int var = 0; var <= 2000; var += 500)
        {
        impedanceValues.emplace(var, 20.0);
        }
    for (long int var = 0; var <= 5000; var += 1000)
        {
        impedanceValues.emplace(var, 50.0);
        }

}

QPainterPath SmithChart::getImpedanceBoundary(double x)
{
    if (x == -1)
        {
        return QPainterPath();
        }

    QPainterPath chartBoundary;
    chartBoundary.addEllipse(QPoint(0, 0), chartRadius, chartRadius);

    auto impClipPath = chartBoundary;
    auto circ = Circle(complex(1, - 1.0 / x), 1.0 / x) * chartRadius;
    impClipPath.addEllipse(QPointF(circ.x(), circ.y()),
                           circ.radius(), circ.radius());
    impClipPath.addEllipse(QPointF(circ.x(), -circ.y()),
                           circ.radius(), circ.radius());

    auto reatClipPath = chartBoundary;
    circ = Circle(x / (x + 1.0), 1.0 / (x + 1.0)) * chartRadius;
    reatClipPath.addEllipse(QPointF(circ.x(), circ.y()),
                            circ.radius(), circ.radius());

    return impClipPath.intersected(reatClipPath);
}
