#pragma once

#include "Light.h"

class AmbientLight : public Light
{
public:

	RGB lightColor;
	Vector lightDirection;
	Vector lightOrigin;
	double radianceScalingFactor;

	AmbientLight();
	void setLightColor(double r, double g, double b);
	void setRadianceScalingFactor(double factor);

};