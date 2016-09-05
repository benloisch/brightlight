#include "GlossySpecular.h"

GlossySpecular::GlossySpecular() {
	phongExponent = 1;
	specularReflectionCoefficient = 1; //reflects all incoming light as default
}

void GlossySpecular::setPhongExponent(double e) {
	phongExponent = e;
}

void GlossySpecular::setReflectionCoefficient(double c) {
	specularReflectionCoefficient = c;
}