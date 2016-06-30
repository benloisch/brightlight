#pragma once

#include "BRDF.h"
//#include "Utilities.h"

const double inversePI = 0.3183098861837906;

class Lambertian : public BRDF
{
public:

	double diffuseReflectionCoefficient;
	RGB diffuseColor;

	Lambertian();
	void setDiffuseReflectionCoefficient(double c);
	void setDiffuseColor(double r, double g, double b);

	inline RGB perfectDiffuseReflectance() {
		return diffuseColor * diffuseReflectionCoefficient * inversePI;
	}

	inline RGB bihemisphericalReflectance() {
		return diffuseColor * diffuseReflectionCoefficient;
	}
};