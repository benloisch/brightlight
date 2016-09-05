#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:

	RGB lightColor;
	double radianceScalingFactor;
	Vector direction;

	DirectionalLight();
	Vector getLightDirection();
	void setLightDirection(double x, double y, double z);
	void setRadianceScalingFactor(double i);
	void setLightColor(double r, double g, double b);
	double getRadianceScalingFactor();
	RGB getLightColor();
	RGB getLightRadiance();

};