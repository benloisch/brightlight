#pragma once

#include "RGB.h"
#include "Vector.h"

using namespace blvector;

const double inversePI = 0.3183098861837906;

class BRDF
{
public:

	virtual double calculateBRDF() { return 0; }
	virtual double calculateBRDF(Vector &wi, Vector &normal, Vector &wo) { return 0; };

	//methods for Lambertian class
	virtual void setReflectionCoefficient(double c) {};

	//methods for GlossySpecular class
	virtual void setPhongExponent(double e) {};
	virtual void setSpecularReflectionCoefficient(double c) {};

};