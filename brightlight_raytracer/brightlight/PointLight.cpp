#include "PointLight.h"

const double PI = 3.14159265359;

PointLight::PointLight() {
	radianceScalingFactor = 1; //default scaling factor
	sampleAmount = 1;
	radius = 0;
}

void PointLight::generateSamples() {
	vector<Point_2D> point2d;
	pointLightSamples.clear();

	int n = (int)sqrt(sampleAmount / 2);
	for (double y = 0; y < n; y++) {
		for (double x = 0; x < n; x++) {
			double xVal = (x / n) + (((double)rand() / (double)(RAND_MAX)) / n);
			double yVal = (y / n) + (((double)rand() / (double)(RAND_MAX)) / n);
			point2d.push_back(Point_2D(xVal, yVal));
		}
	}

	n = (int)sqrt(sampleAmount / 2);
	for (double y = 0; y < n; y++) {
		for (double x = 0; x < n; x++) {
			double xVal = (x / n) + (((double)rand() / (double)(RAND_MAX)) / n);
			double yVal = (y / n) + (((double)rand() / (double)(RAND_MAX)) / n);
			point2d.push_back(Point_2D(xVal, yVal));
		}
	}

	for (int i = 0; i < sampleAmount; i++) {
		double cos_phi = cos(2.0 * PI * point2d[i].x);
		double sin_phi = sin(2.0 * PI * point2d[i].x);
		double cos_theta = pow((1.0 - point2d[i].y), 1.0 / (0 + 1.0));
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		double z = sin_theta * cos_phi;
		double x = sin_theta * sin_phi;
		double y = cos_theta;
		if (i < int(sampleAmount / 2)) 
			pointLightSamples.push_back(Vector(x, y, z, 0));
		else 
			pointLightSamples.push_back(Vector(x, -y, z, 0));
	}
}

void PointLight::setPointLightRadius(double radius) {
	this->radius = radius;
}

double PointLight::getRadius() {
	return radius;
}

vector<Vector> PointLight::getSamplePoints() {
	return pointLightSamples;
}

void PointLight::setAreaPointLightSamplePointAmount(int samplePointAmount) {
	sampleAmount = samplePointAmount * 2;
}

int PointLight::getNumberOfSamplePoints() {
	return sampleAmount;
}

Vector PointLight::getLightOrigin() {
	return origin;
}

void PointLight::setLightOrigin(double x, double y, double z) {
	origin.x = x;
	origin.y = y;
	origin.z = z;
}

void PointLight::setLightColor(double r, double g, double b) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
}

void PointLight::setRadianceScalingFactor(double i) {
	radianceScalingFactor = i;
}

double PointLight::getRadianceScalingFactor() {
	return radianceScalingFactor;
}

RGB PointLight::getLightColor() {
	return lightColor;
}

RGB PointLight::getLightRadiance() {
	return lightColor * radianceScalingFactor;
}