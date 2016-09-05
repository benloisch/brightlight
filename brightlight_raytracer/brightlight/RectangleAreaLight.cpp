#include "RectangleAreaLight.h"

RectangleAreaLight::RectangleAreaLight() {
	radianceScalingFactor = 1; //default scaling factor
	rectangleHeight = 1;
	rectangleWidth = 1;
	samplePointWidth = 1;
}

RectangleAreaLight::~RectangleAreaLight() {

}

void RectangleAreaLight::setRectangleAreaLightWidthHeight(double x, double y) {
	rectangleWidth = x;
	rectangleHeight = y;
}

void RectangleAreaLight::setLightOrigin(double x, double y, double z) {
	lightOrigin.x = x;
	lightOrigin.y = y;
	lightOrigin.z = z;
}

void RectangleAreaLight::setLightDirection(double x, double y, double z) {
	direction.x = x;
	direction.y = y;
	direction.z = z;
	direction.normalize();
}

Vector RectangleAreaLight::getLightDirection() {
	return direction;
}

void RectangleAreaLight::setRectangleAreaLightMatrix(double radianRotation) {
	Vector right;
	Vector up;
	
	if ((direction.x == 0 && direction.y == 1 && direction.z == 0) || (direction.x == 0 && direction.y == -1 && direction.z == 0)){
		right.x = 1;
	}
	else {
		right = Vector(0, 1, 0, 0) ^ direction;
	}

	Matrix rotateRightAxis;
	rotateRightAxis.setRotArb(direction.x, direction.y, direction.z, radianRotation);

	right = right * rotateRightAxis;

	up = direction ^ right;

	areaLightMatrix.setRow1(right.x, right.y, right.z, 0);
	areaLightMatrix.setRow2(up.x, up.y, up.z, 0);
	areaLightMatrix.setRow3(direction.x, direction.y, direction.z, 0);
	areaLightMatrix.setRow4(lightOrigin.x, lightOrigin.y, lightOrigin.z, 1);
}

void RectangleAreaLight::setRectangleAreaLightSamplePointAmount(int samplePointAmount) {
	double area = samplePointAmount;
	double ratio = rectangleHeight / rectangleWidth;
	samplePointWidth = int(round(sqrt(area / ratio)));
	samplePointHeight = int(round(sqrt(area * ratio)));
}

void RectangleAreaLight::generateSamples() {
	samplePoints.clear();

	for (double y = 0; y < samplePointHeight; y++) {
		for (double x = 0; x < samplePointWidth; x++) {
			double xVal = (x / samplePointWidth + ((double)rand() / (double)(RAND_MAX)) / samplePointWidth);
			double yVal = (y / samplePointHeight + ((double)rand() / (double)(RAND_MAX)) / samplePointHeight);
			samplePoints.push_back(Vector(xVal, yVal, 0, 1));
		}
	}

	//map points from [0,1] to [-1,-1] and transform to area matrix
	for (unsigned int i = 0; i < samplePoints.size(); i++) {
		samplePoints[i].x = ((samplePoints[i].x * 2) - 1) * rectangleWidth;
		samplePoints[i].y = ((samplePoints[i].y * 2) - 1) * rectangleHeight;
		samplePoints[i] = samplePoints[i] * areaLightMatrix;
	}
}

int RectangleAreaLight::getNumberOfSamplePoints() {
	return samplePointWidth * samplePointHeight;
}

vector<Vector> RectangleAreaLight::getSamplePoints() {
	return samplePoints;
}

void RectangleAreaLight::setLightColor(double r, double g, double b) {
	lightColor.r = r;
	lightColor.g = g;
	lightColor.b = b;
}

void RectangleAreaLight::setRadianceScalingFactor(double i) {
	radianceScalingFactor = i;
}

double RectangleAreaLight::getRadianceScalingFactor() {
	return radianceScalingFactor;
}

RGB RectangleAreaLight::getLightColor() {
	return lightColor;
}

RGB RectangleAreaLight::getLightRadiance() {
	return lightColor * radianceScalingFactor;
}