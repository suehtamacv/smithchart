#ifndef ADMITTANCE_H
#define ADMITTANCE_H

#include "Complex.h"

class Impedance;

/**
 * @brief The Admittance class represents an admittance, measured in Siemens (S).
 */
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
    complex operator/(const Admittance &other) const;
    bool operator==(const Admittance &other) const;

private:
    complex admittance;
};

#endif // ADMITTANCE_H
