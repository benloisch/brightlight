#include "Lambertian.h"

Lambertian::Lambertian() {
	diffuseReflectionCoefficient = 1; //reflects all incoming light as default
}

void Lambertian::setDiffuseColor(double r, double g, double b) {
	diffuseColor.r = r;
	diffuseColor.g = g;
	diffuseColor.b = b;
}

void Lambertian::setDiffuseReflectionCoefficient(double c) {
	diffuseReflectionCoefficient = c;
}