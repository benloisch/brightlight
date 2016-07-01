#pragma once

#include "Material.h"
#include "Lambertian.h"
#include "BRDF.h"
#include <math.h>

#define dotproductmax(a, b) ((a > b) ? a : b)

class Matte : public Material
{
public:
	BRDF *ambientBRDF;
	BRDF *diffuseBRDF;

	BRDF* getAmbientBRDF();
	BRDF* getDiffuseBRDF();

	inline RGB shade(Shade s, vector<Light*> ambient, vector<Light*> directional, vector<Light*> point) {
		RGB rgbAmbient;
		//calculate ambient light
		for (unsigned int i = 0; i < ambient.size(); i++) {
			rgbAmbient += ambientBRDF->bihemisphericalReflectance() * ambient[i]->getLightRadiance();
		}

		RGB rgbDirectional;
		for (unsigned int i = 0; i < directional.size(); i++) {
			rgbDirectional += diffuseBRDF->perfectDiffuseReflectance() * directional[i]->getLightRadiance() * dotproductmax(((directional[i]->getLightDirection() * -1) * s.normal), 0);
		}

		return rgbAmbient + rgbDirectional;
	}

	Matte();
	~Matte();

};