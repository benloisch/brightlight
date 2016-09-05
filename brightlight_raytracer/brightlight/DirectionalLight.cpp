#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
	radianceScalingFactor = 1; //default scaling factor
}

Vector DirectionalLight::getLightDirection() {
	return direction;
}

void DirectionalLight::setLightDirection(double x, double y, double z) {
	direction.x = x;
	direction.y = y;
	direction.z = z;
	direction.normalize();
}

void DirectionalLight::setLightColor(double r, double g, double b) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
}

void DirectionalLight::setRadianceScalingFactor(double i) {
	radianceScalingFactor = i;
}

double DirectionalLight::getRadianceScalingFactor() {
	return radianceScalingFactor;
}

RGB DirectionalLight::getLightColor() {
	return lightColor;
}

RGB DirectionalLight::getLightRadiance() {
	return lightColor * radianceScalingFactor;
}