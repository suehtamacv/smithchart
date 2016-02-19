#ifndef SMITHCHARTTRANSFORMATION_H
#define SMITHCHARTTRANSFORMATION_H

#include "MoebiusTransformation.h"

class Impedance;
class Admittance;

class SmithChartTransformation : public MoebiusTransformation
{
public:
    SmithChartTransformation();

    complex findPoint(const Impedance &) const;
    complex findPoint(const Admittance &) const;

    Impedance findImpedance(complex &) const;
    Admittance findAdmittance(complex &) const;
};

#endif // SMITHCHARTTRANSFORMATION_H
