#include "include/MoebiusTranformations/MoebiusTransformation.h"

MoebiusTransformation::MoebiusTransformation
(complex a, complex b, complex c, complex d) : a(a), b(b), c(c), d(d)
{
    if (c == complex(0, 0) && d == complex(0, 0))
        {
        c = d = 1;
        }
}

MoebiusTransformation MoebiusTransformation::inverse()
{
    return MoebiusTransformation(d, -b, -c, a);
}

complex MoebiusTransformation::transform(complex z)
{
    return (a * z + b) / (c * z + d);
}
