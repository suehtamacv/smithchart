#ifndef IMPEDANCELINEINPUT_H
#define IMPEDANCELINEINPUT_H

#include "Complex.h"
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <memory>

class ImpedanceLineInput : public QHBoxLayout
{
public:
    ImpedanceLineInput(QWidget *parent = 0);

    complex getValue();

private:
    std::unique_ptr<QDoubleSpinBox> Resistance;
    std::unique_ptr<QDoubleSpinBox> Reactance;
    std::unique_ptr<QLabel> LabelP;
    std::unique_ptr<QLabel> LabelOhm;
};

#endif // IMPEDANCELINEINPUT_H
