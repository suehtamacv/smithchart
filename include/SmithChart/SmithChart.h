#ifndef SMITHCHART_H
#define SMITHCHART_H

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include <QWidget>
#include "include/GeneralClasses/Impedance.h"
#include "include/GeneralClasses/Circle.h"
#include "include/MoebiusTranformations/SmithChartTransformation.h"

class Admitttance;
class Circle;

class SmithChart : public QWidget
{
    Q_OBJECT

public:
    SmithChart(Impedance Z0, QWidget *parent = 0);
    SmithChart(Admittance Y0, QWidget *parent = 0);

    void drawImpedance(const Impedance &impedance);
    void drawAdmittance(const Admittance &admittance);

    void setCharacteristicImpedance(Impedance &impedance);

private:
    Impedance characteristicImpedance;
    SmithChartTransformation chartTransformation;

    std::vector<Impedance> drawnImpedances;

    std::shared_ptr<QLabel> chart;
    std::shared_ptr<QPicture> chartPicture;

    unsigned int chartRadius;

    std::set<std::pair<int, double>> impedanceValues;
    std::map<double, double> previousImpedance;
    std::map<double, QPainterPath> impedanceBoundaries;
    QPainterPath getImpedanceBoundary(double x);

    void setupInterface();
    void resizeEvent(QResizeEvent *);

    void drawSmithChart(std::shared_ptr<QPainter> painter);
    void drawImpedances(std::shared_ptr<QPainter> painter);
    void drawLabels(std::shared_ptr<QPainter> painter);

    void povoateChartValues();

private slots:
    void drawChart();

signals:
    void redraw();

};

#endif // SMITHCHART_H
