#include "Matte.h"

Matte::Matte() {
	ambientBRDF = new Lambertian;
	diffuseBRDF = new Lambertian;
}

Matte::~Matte() {
	delete ambientBRDF;
	delete diffuseBRDF;
}

BRDF* Matte::getAmbientBRDF() {
	return ambientBRDF;
}

BRDF* Matte::getDiffuseBRDF() {
	return diffuseBRDF;
}