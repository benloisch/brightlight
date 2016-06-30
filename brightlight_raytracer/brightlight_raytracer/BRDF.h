#pragma once

#include "Shade.h"
#include "RGB.h"
#include "Vector.h"

using namespace blvector;

class BRDF
{
public:

	virtual RGB perfectDiffuseReflectance() = 0;
	virtual RGB bihemisphericalReflectance() = 0;

	//methods for Lambertian class
	virtual void setDiffuseReflectionCoefficient(double c) {};
	virtual void setDiffuseColor(double r, double g, double b) {};

};