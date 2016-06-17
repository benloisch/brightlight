#include "Sphere.h"
#include <math.h>
#include <float.h>

Sphere::Sphere(double radius, double xOrigin, double yOrigin, double zOrigin) {
	this->radius = radius;
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	this->zOrigin = zOrigin;
	this->rgb.r = 0;
	this->rgb.g = 0;
	this->rgb.b = 0;
}

void Sphere::setColor(unsigned char r, unsigned char g, unsigned char b) {
	this->rgb.r = r;
	this->rgb.g = g;
	this->rgb.b = b;
}

void Sphere::intersectRay(double &depth, Vector rayIn, Camera cam) {
	Vector sphereOrigin(xOrigin, yOrigin, zOrigin, 0);

	double a = rayIn * rayIn;
	double b = ((cam.cameraOrigin - sphereOrigin) * rayIn) * 2;
	double c = ((cam.cameraOrigin - sphereOrigin) * (cam.cameraOrigin - sphereOrigin)) - (radius * radius);

	double discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0) {
		depth = DBL_MAX;
		return;
	}

	double t1 = (-b + sqrt(((b * b) - (4 * a * c)))) / (2 * a);
	double t2 = (-b - sqrt(((b * b) - (4 * a * c)))) / (2 * a);

	depth = (t1 < t2) ? t1 : t2;
	if (depth <= 0) {
		depth = DBL_MAX;
		return;
	}

	//depth gets returned through parameter
}

RGB Sphere::getColor() {
	return rgb;
}