#ifndef SMITHCHART_H
#define SMITHCHART_H

#include <complex>
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

typedef std::complex<double> complex;

class SmithChart : public QWidget
{
    Q_OBJECT

public:
    SmithChart(Impedance Z0, QWidget *parent = 0);
    SmithChart(Admittance Y0, QWidget *parent = 0);

    void drawImpedance(const Impedance &impedance);
    void drawAdmittance(const Admittance &admittance);

private:
    Impedance characteristicImpedance;
    SmithChartTransformation chartTransformation;

    std::vector<Impedance> drawnImpedances;

    std::shared_ptr<QLabel> chart;
    std::shared_ptr<QPicture> chartPicture;

    unsigned int chartRadius;

    std::set<std::pair<int, double>> impedanceValues;
    std::map<double, double> previousImpedance;
    QPainterPath getImpedanceBoundary(double x);

    void setupInterface();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void drawSmithChart(QPainter *painter);
    void drawImpedances(QPainter *painter);

    void povoateChartValues();
};

#endif // SMITHCHART_H
