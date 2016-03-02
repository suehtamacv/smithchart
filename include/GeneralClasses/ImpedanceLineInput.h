#ifndef IMPEDANCELINEINPUT_H
#define IMPEDANCELINEINPUT_H

#include "Complex.h"
#include "Impedance.h"
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <memory>

class ImpedanceLineInput : public QHBoxLayout
{
public:
    ImpedanceLineInput(QWidget *parent = 0);
    Impedance getValue();

signals:
    void valueChanged(Impedance);

private:
    std::shared_ptr<QDoubleSpinBox> Resistance;
    std::shared_ptr<QDoubleSpinBox> Reactance;
    std::shared_ptr<QLabel> LabelP;
    std::shared_ptr<QLabel> LabelOhm;

private slots:
    void emitValueChanged();
};

#endif // IMPEDANCELINEINPUT_H
