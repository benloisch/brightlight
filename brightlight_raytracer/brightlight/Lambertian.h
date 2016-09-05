#pragma once

#include "BRDF.h"

class Lambertian : public BRDF
{
public:

	double diffuseReflectionCoefficient;

	Lambertian();
	void setReflectionCoefficient(double c);

	inline double calculateBRDF() {
		return diffuseReflectionCoefficient * inversePI;
	}
};