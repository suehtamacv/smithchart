#ifndef SMITHCHARTTRANSFORMATION_H
#define SMITHCHARTTRANSFORMATION_H

#include "MoebiusTransformation.h"
#include "include/GeneralClasses/Impedance.h"

class Impedance;
class Admittance;

class SmithChartTransformation : public MoebiusTransformation
{
public:
    SmithChartTransformation(Impedance characteristicImpedance);
    SmithChartTransformation(Admittance characteristicAdmittance);

    complex findPoint(const Impedance &) const;
    complex findPoint(const Admittance &) const;

    Impedance findImpedance(complex &) const;
    Admittance findAdmittance(complex &) const;

private:
    Impedance characteristicImpedance;
};

#endif // SMITHCHARTTRANSFORMATION_H
