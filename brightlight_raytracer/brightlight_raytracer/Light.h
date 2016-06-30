#pragma once

#include "Vector.h"
#include "RGB.h"

using namespace blvector;

class Light
{
public:

	virtual void setLightIntensity(double i) = 0;
	virtual void setLightColor(double r, double g, double b) = 0;
	virtual double getLightIntensity() = 0;
	virtual RGB getLightColor() = 0;
	virtual RGB getLightRadiance() = 0; //used for all lights
	virtual Vector getLightDirection() { return Vector(0, 0, 0, 0); }; //used for directional and point lights
	virtual Vector getLightOrigin() { return Vector(0, 0, 0, 0); }; //used for point lights

};