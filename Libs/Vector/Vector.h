#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "Number.h"
class  Vector {
public:
    Vector(Number a, Number b);
    Number get_polar_radius();
    Number get_polar_angle();
    Number x;
    Number y;
};

Vector  AddVectors(Vector a, Vector b);

const Vector ONE_VECTOR = Vector(1, 1);
const Vector ZERO_VECTOR = Vector(0, 0);

#endif //VECTOR_VECTOR_H
