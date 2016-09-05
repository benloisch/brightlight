#include "Vector.h"

using namespace blvector;

Vector::Vector() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

Vector::Vector(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
