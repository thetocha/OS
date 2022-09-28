#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H

#include<cmath>
class Number {
public:
    Number();
    Number(double x);
    double add(double a);
    Number add(Number a);
    double sub(double a);
    double mul(double a);
    double div(double a);
    double my_sqrt();
public:
    double value;
};

Number NumberCreator(double x);

const Number ZERO_NUMBER = Number(0);
const Number ONE_NUMBER = Number(1);

#endif //NUMBER_NUMBER_H
