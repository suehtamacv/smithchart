#include "include/SmithChart/SmithChart.h"
#include "include/GeneralClasses/Impedance.h"
#include "include/GeneralClasses/Admittance.h"
#include "include/GeneralClasses/Circle.h"
#include <algorithm>
#include <QLayout>
#include <QResizeEvent>

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
    setFixedSize(700, 700);

    chart = std::make_shared<QLabel>(this);
    chartPicture = std::make_shared<QPicture>();
    chart->setContentsMargins(0, 0, 0, 0);
    chart->setPicture(*chartPicture);
    chart->setSizePolicy(QSizePolicy::Expanding,
                         QSizePolicy::Expanding);

    auto HLayout = new QHBoxLayout(this);
    HLayout->addWidget(chart.get());
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
    drawLabels(painter);

    delete painter;
}

void SmithChart::resizeEvent(QResizeEvent *)
{
    impedanceBoundaries.clear();

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

    if (impedanceBoundaries.count(x))
        {
        return impedanceBoundaries.at(x);
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

    impedanceBoundaries.emplace(x, impClipPath.intersected(reatClipPath));
    return impClipPath.intersected(reatClipPath);
}

void SmithChart::drawLabels(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setClipping(false);

    painter->drawEllipse(QPointF(0, 0), chartRadius * 1.1, chartRadius * 1.1);

    QFont font = painter->font();
    font.setPixelSize(8);
    painter->setFont(font);

    double labels[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.2,
                       1.4, 1.6, 1.8, 2.0, 3.0, 4.0, 5.0, 10.0, 20.0, 50.0
                      };

    painter->rotate(-90);
    for (auto r : labels)
        {
        QRectF rect(QPointF(0, (r - 1) / (r + 1)) * chartRadius,
                    QPointF(0, (r - 1) / (r + 1)) * chartRadius);
        auto br = painter->boundingRect(rect, QString::number(r));
        painter->fillRect(br, painter->background());
        painter->drawText(QPointF(0, (r - 1) / (r + 1)) * chartRadius +
                          QPointF(0, font.pixelSize()), QString::number(r));
        }
    painter->rotate(90);
}
