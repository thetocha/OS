#include "Vector.h"


Vector::Vector(Number a, Number b) : x(a), y(b) {};
Number Vector::get_polar_radius() {
    Number x_square = x.mul(x.value);
    Number y_square = y.mul(y.value);
    Number r_square = x_square.add(y_square.value);
    return r_square.my_sqrt();
}
Number Vector::get_polar_angle() {
    Number tan = y.div(x.value);
    Number my_atan = Number(atan(tan.value));
    return my_atan;
}
Vector AddVectors(Vector a, Vector b) {
    Number newX = Number(a.x.value + b.x.value);
    Number newY = Number(a.y.value + b.y.value);
    Vector sum = Vector(newX, newY);
    return sum;
}


