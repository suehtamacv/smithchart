#ifndef MOEBIUSTRANSFORMATION_H
#define MOEBIUSTRANSFORMATION_H

#include <complex>

class Impedance;
class Admittance;

typedef std::complex<double> complex;

/**
 * @brief The MoebiusTransformation class represents a Möbius Transformation.
 *
 * Given a complex number z, the Möbius transformation maps z to f(z) =
 * (a * z + b) / (c * z + d), where a, b, c and d are arbitrary complex numbers.
 */
class MoebiusTransformation
{
public:
    MoebiusTransformation(complex a, complex b, complex c, complex d);

    complex transform(complex z);

    MoebiusTransformation inverse();

private:
    complex a;
    complex b;
    complex c;
    complex d;
};

#endif // MOEBIUSTRANSFORMATION_H
