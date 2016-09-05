#include "Sphere.h"

Sphere::Sphere() {
	radius = radius;
	xOrigin = 0;
	yOrigin = 0;
	zOrigin = 0;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;

	tag = "none";
}

Sphere::~Sphere() {
	delete material;
}

void Sphere::setMaterial(Material* mat) {
	material = mat;
};

Material* Sphere::getMaterial() {
	return material;
}

void Sphere::setRadius(double r) {
	radius = r;
}

void Sphere::setOrigin(double x, double y, double z) {
	xOrigin = x;
	yOrigin = y;
	zOrigin = z;
}

void Sphere::setColor(double r, double g, double b) {
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

