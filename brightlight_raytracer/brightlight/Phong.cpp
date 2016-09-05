#include "Phong.h"

Phong::Phong() {
	ambientBRDF = new Lambertian;
	diffuseBRDF = new Lambertian;
	specularBRDF = new GlossySpecular;
}

Phong::~Phong() {
	delete ambientBRDF;
	delete diffuseBRDF;
	delete specularBRDF;
}

BRDF* Phong::getAmbientBRDF() {
	return ambientBRDF;
}

BRDF* Phong::getDiffuseBRDF() {
	return diffuseBRDF;
}

BRDF* Phong::getSpecularBRDF() {
	return specularBRDF;
}