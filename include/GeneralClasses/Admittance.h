#ifndef ADMITTANCE_H
#define ADMITTANCE_H

#include <complex>

typedef std::complex<double> complex;

class Impedance;

class Admittance
{
    friend class Impedance;

public:
    Admittance(complex admittance);
    Admittance(double Abs, double Theta);
    Admittance(const Admittance &other);
    Admittance(const Impedance &other);

    Impedance toImpedance() const;

    Admittance operator -() const;

    Admittance& operator+=(const Admittance &other);
    Admittance& operator+=(const Impedance &other);
    Admittance& operator-=(const Admittance &other);
    Admittance& operator-=(const Impedance &other);

    Admittance operator+(const Admittance &other) const;
    Admittance operator-(const Admittance &other) const;


private:
    std::complex<double> admittance;
};

#endif // ADMITTANCE_H
