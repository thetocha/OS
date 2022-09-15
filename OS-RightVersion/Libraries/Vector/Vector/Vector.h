#pragma once

#ifdef VECTORLIBRARY_EXPORTS
#define VECTORIBRARY_API __declspec(dllexport)
#else
#define VECTORIBRARY_API __declspec(dllimport)
#endif

#include "Number.h"
class VECTORIBRARY_API Vector {
public:
	Vector(Number a, Number b);
	Number get_polar_radius();
	Number get_polar_angle();
	Number x;
	Number y;
};

Vector VECTORIBRARY_API AddVectors(Vector a, Vector b);

extern const VECTORIBRARY_API Vector ZERO_VECTOR;
extern const VECTORIBRARY_API Vector ONE_VECTOR;

