#include "Sphere.h"

Sphere::Sphere() {
	radius = radius;
	xOrigin = 0;
	yOrigin = 0;
	zOrigin = 0;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
}

void Sphere::setRadius(double r) {
	radius = r;
}

void Sphere::setOrigin(double x, double y, double z) {
	xOrigin = x;
	yOrigin = y;
	zOrigin = z;
}

void Sphere::setColor(unsigned char r, unsigned char g, unsigned char b) {
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

