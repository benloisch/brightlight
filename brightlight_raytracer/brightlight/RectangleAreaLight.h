#pragma once

#include "Light.h"

class RectangleAreaLight : public Light
{
public:

	RGB lightColor;
	double radianceScalingFactor;
	vector<Vector> samplePoints;
	Vector direction;
	int samplePointWidth;
	int samplePointHeight;
	Matrix areaLightMatrix;
	Vector lightOrigin;
	double rectangleWidth;
	double rectangleHeight;

	void generateSamples();
	void setLightOrigin(double x, double y, double z);
	void setLightDirection(double x, double y, double z);
	Vector getLightDirection();
	void setRectangleAreaLightMatrix(double radianRotation);
	void setRectangleAreaLightSamplePointAmount(int samplePointAmount);
	void setRectangleAreaLightWidthHeight(double x, double y);
	int getNumberOfSamplePoints();
	vector<Vector> getSamplePoints();
	RectangleAreaLight();
	~RectangleAreaLight();
	void setRadianceScalingFactor(double i);
	void setLightColor(double r, double g, double b);
	double getRadianceScalingFactor();
	RGB getLightColor();
	RGB getLightRadiance();

};