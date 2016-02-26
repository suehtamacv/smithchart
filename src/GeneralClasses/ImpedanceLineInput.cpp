#include "include/GeneralClasses/ImpedanceLineInput.h"

ImpedanceLineInput::ImpedanceLineInput(QWidget *parent) :
    QHBoxLayout(parent)
{
    Resistance = std::unique_ptr<QDoubleSpinBox>(new QDoubleSpinBox);
    Resistance->setSingleStep(0.1);
    Resistance->setMaximumWidth(120);

    Reactance = std::unique_ptr<QDoubleSpinBox>(new QDoubleSpinBox);
    Reactance->setSingleStep(0.1);
    Reactance->setMaximumWidth(120);
    Reactance->setSuffix("j");

    Resistance->setRange(1.0, std::numeric_limits<int>::max());
    Reactance->setRange(-std::numeric_limits<int>::min(),
                        std::numeric_limits<int>::max());

    LabelP = std::unique_ptr<QLabel>(new QLabel("+"));
    LabelP->setFixedWidth(15);
    LabelP->setAlignment(Qt::AlignCenter);

    LabelOhm = std::unique_ptr<QLabel>(new QLabel("Ω"));
    LabelOhm->setFixedWidth(15);
    LabelOhm->setAlignment(Qt::AlignCenter);

    addWidget(Resistance.get());
    addWidget(LabelP.get());
    addWidget(Reactance.get());
    addWidget(LabelOhm.get());

    setSizeConstraint(QLayout::SetMinimumSize);
}

complex ImpedanceLineInput::getValue()
{
    return complex(Resistance->value(), Reactance->value());
}
