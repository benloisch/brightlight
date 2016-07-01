#pragma once

#include "Vector.h"
#include "RGB.h"

using namespace blvector;

class Light
{
public:

	virtual void setRadianceScalingFactor(double i) = 0;
	virtual void setLightColor(double r, double g, double b) = 0;
	virtual double getRadianceScalingFactor() = 0;
	virtual RGB getLightColor() = 0; 
	virtual RGB getLightRadiance() = 0; 
	virtual Vector getLightDirection() { return Vector(0, 0, 0, 0); }; //used for directional and point lights
	virtual Vector getLightOrigin() { return Vector(0, 0, 0, 0); }; //used for point lights
	virtual void setLightOrigin(double x, double y, double z) {}; //used for point lights
	virtual void setLightDirection(double x, double y, double z) {}; //used for directional lights

};