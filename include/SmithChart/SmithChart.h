#ifndef SMITHCHART_H
#define SMITHCHART_H

#include <memory>
#include <QWidget>

class SmithChart : public QWidget
{
    Q_OBJECT

public:
    SmithChart(QWidget *parent = 0);

private:
    void setupInterface();
};

#endif // SMITHCHART_H
