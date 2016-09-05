#pragma once

#include "BRDF.h"

class GlossySpecular : public BRDF
{
public:

	double phongExponent;
	double specularReflectionCoefficient;

	GlossySpecular();
	void setPhongExponent(double e);
	void setReflectionCoefficient(double c);

	inline double calculateBRDF(Vector &wi, Vector &normal, Vector &wo) {
		Vector r = ((wi * -1) + (normal * ((normal * wi) * 2)));
		return specularReflectionCoefficient * pow(abs((r * wo)), phongExponent);
	}
};