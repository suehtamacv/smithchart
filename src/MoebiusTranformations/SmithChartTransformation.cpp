#include "include/MoebiusTranformations/SmithChartTransformation.h"
#include "include/GeneralClasses/Admittance.h"
#include "include/GeneralClasses/Impedance.h"
#include "boost/assert.hpp"

SmithChartTransformation::SmithChartTransformation() :
    MoebiusTransformation(1, 1, -1, 1)
{

}

complex SmithChartTransformation::findPoint(const Impedance &impedance) const
{
    return transform(impedance.getImpedance());
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
    BOOST_ASSERT_MSG(abs(z) <= 1, "Point not in the Smith Chart: its absolute"
                     " value is greater than 1.");
    return findImpedance(z).toAdmittance();
}
