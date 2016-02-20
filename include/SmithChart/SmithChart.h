#ifndef SMITHCHART_H
#define SMITHCHART_H

#include <memory>
#include <QWidget>
#include <QPainter>

class SmithChart : public QWidget
{
    Q_OBJECT

public:
    SmithChart(QWidget *parent = 0);

private:
    void setupInterface();
    void paintEvent(QPaintEvent *);

    void drawSmithChart();
};

#endif // SMITHCHART_H
