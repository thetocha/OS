#include"Number.h"

Number::Number() : value(0) {};
Number::Number(double x) : value(x) {};
double Number::add(double a){
	return a + value;
}
Number Number::add(Number a) {
	return value + a.value;
}
double Number::sub(double a) {
	return value - a;
}
double Number::mul(double a) {
	return value * a;
}
double Number::div(double a) {
	return value / a;
}
double Number::my_sqrt() {
	return sqrt(value);
}

const Number ZERO_NUMBER = Number(0);
const Number ONE_NUMBER = Number(1);

Number NumberCreator(double x) {
	Number num = Number(x);
	return num;
}