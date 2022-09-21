#include <iostream>
#include "Vector.h"

int main()
{
    Vector vector = Vector(2, 3);
    Vector vec = Vector(3, 2);
    std::cout << vector.x.value << std::endl;
    Number a(5);
    Number a1 = ONE_NUMBER;
    a = NumberCreator(3);
    std::cout << a.value << std::endl;
    std::cout << a1.value << std::endl;
    Vector v1 = ONE_VECTOR;
    std::cout << v1.x.value << std::endl;
    std::cout << vector.get_polar_radius().value << std::endl;
    Vector sum = AddVectors(vec, vector);
    std::cout << sum.x.value << std::endl;
}