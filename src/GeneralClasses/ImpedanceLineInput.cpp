#include "include/GeneralClasses/ImpedanceLineInput.h"

ImpedanceLineInput::ImpedanceLineInput(QWidget *parent) :
    QHBoxLayout(parent)
{
    Resistance = std::shared_ptr<QDoubleSpinBox>(new QDoubleSpinBox);
    Resistance->setSingleStep(0.1);
    Resistance->setMaximumWidth(120);

    Reactance = std::shared_ptr<QDoubleSpinBox>(new QDoubleSpinBox);
    Reactance->setSingleStep(0.1);
    Reactance->setMaximumWidth(120);
    Reactance->setSuffix("j");

    Resistance->setRange(0.1, std::numeric_limits<int>::max());
    Reactance->setRange(-std::numeric_limits<int>::min(),
                        std::numeric_limits<int>::max());

    LabelP = std::shared_ptr<QLabel>(new QLabel("+"));
    LabelP->setFixedWidth(15);
    LabelP->setAlignment(Qt::AlignCenter);

    LabelOhm = std::shared_ptr<QLabel>(new QLabel("Ω"));
    LabelOhm->setFixedWidth(15);
    LabelOhm->setAlignment(Qt::AlignCenter);

    addWidget(Resistance.get());
    addWidget(LabelP.get());
    addWidget(Reactance.get());
    addWidget(LabelOhm.get());

    setSizeConstraint(QLayout::SetMinimumSize);

    connect(Resistance.get(), SIGNAL(valueChanged(double)), this,
            SLOT(emitValueChanged()));
    connect(Reactance.get(), SIGNAL(valueChanged(double)), this,
            SLOT(emitValueChanged()));
}

Impedance ImpedanceLineInput::getValue()
{
    return Impedance(complex(Resistance->value(), Reactance->value()));
}

void ImpedanceLineInput::valueChanged(Impedance)
{
}

void ImpedanceLineInput::emitValueChanged()
{
    emit valueChanged(getValue());
}
