#pragma once

#include "Light.h"

class PointLight : public Light
{
public:

	RGB lightColor;
	double radianceScalingFactor;
	Vector origin;

	vector<Vector> pointLightSamples;
	int sampleAmount;
	double radius;

	PointLight();
	double getRadius();
	void setAreaPointLightSamplePointAmount(int samplePointAmount);
	int getNumberOfSamplePoints(); //used for area lights
	void generateSamples(); // used for area lights
	vector<Vector> getSamplePoints(); //used for area lights
	Vector getLightOrigin();
	void setLightOrigin(double x, double y, double z);
	void setRadianceScalingFactor(double i);
	void setLightColor(double r, double g, double b);
	double getRadianceScalingFactor();
	RGB getLightColor();
	RGB getLightRadiance();
	void setPointLightRadius(double radius);

};