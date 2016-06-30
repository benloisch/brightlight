#pragma once

#include "Material.h"
#include "Lambertian.h"
#include "BRDF.h"

class Matte : public Material
{
public:
	BRDF *ambientBRDF;
	BRDF *diffuseBRDF;

	inline RGB shade() {
		RGB rgb;

		return rgb;
	}

	Matte();
	~Matte();

};