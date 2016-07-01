#pragma once

#include "Light.h"

class AmbientLight : public Light
{
public:

	RGB lightColor;
	double radianceScalingFactor;

	AmbientLight();
	void setRadianceScalingFactor(double i);
	void setLightColor(double r, double g, double b);
	double getRadianceScalingFactor();
	RGB getLightColor();
	RGB getLightRadiance();

};