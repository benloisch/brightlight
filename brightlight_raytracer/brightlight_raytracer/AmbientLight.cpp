#include "AmbientLight.h"

AmbientLight::AmbientLight() {
	radianceScalingFactor = 1; //default scaling factor
}

void AmbientLight::setLightColor(double r, double g, double b) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
}

void AmbientLight::setRadianceScalingFactor(double i) {
	radianceScalingFactor = i;
}

double AmbientLight::getRadianceScalingFactor() {
	return radianceScalingFactor;
}

RGB AmbientLight::getLightColor() {
	return lightColor;
}

RGB AmbientLight::getLightRadiance() {
	return lightColor * radianceScalingFactor;
}