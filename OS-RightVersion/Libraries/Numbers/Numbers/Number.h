#pragma 
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

extern const Number ZERO_NUMBER;
extern const Number ONE_NUMBER;