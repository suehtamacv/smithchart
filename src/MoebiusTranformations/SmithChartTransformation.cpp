#include "include/MoebiusTranformations/SmithChartTransformation.h"
#include "include/GeneralClasses/Admittance.h"
#include "boost/assert.hpp"

SmithChartTransformation::SmithChartTransformation
(Impedance characteristicImpedance) :
    MoebiusTransformation(1, 1, -1, 1),
    characteristicImpedance(characteristicImpedance)
{
    if (characteristicImpedance == Impedance(0))
        {
        characteristicImpedance = Impedance(1);
        }
}

SmithChartTransformation::SmithChartTransformation
(Admittance characteristicAdmittance) :
    SmithChartTransformation(characteristicAdmittance.toImpedance())
{

}

complex SmithChartTransformation::findPoint(const Impedance &impedance) const
{
    return transform(impedance / characteristicImpedance);
}

complex SmithChartTransformation::findPoint(const Admittance &admittance) const
{
    return findPoint(admittance.toImpedance());
}

Impedance SmithChartTransformation::findImpedance(complex &z) const
{
    BOOST_ASSERT_MSG(abs(z) <= 1, "Point not in the Smith Chart: its absolute"
                     " value is greater than 1.");
    return Impedance(inverse().transform(z));
}

Admittance SmithChartTransformation::findAdmittance(complex &z) const
{
    return findImpedance(z).toAdmittance();
}
