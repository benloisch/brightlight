#include "Lambertian.h"

Lambertian::Lambertian() {
	diffuseReflectionCoefficient = 1; //reflects all incoming light as default
}

void Lambertian::setReflectionCoefficient(double c) {
	diffuseReflectionCoefficient = c;
}