#include "AmbientLight.h"

AmbientLight::AmbientLight() {
	radianceScalingFactor = 1; //default scaling factor
}

void AmbientLight::setLightColor(double r, double g, double b) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
}

void AmbientLight::setRadianceScalingFactor(double factor) {
	radianceScalingFactor = factor;
}