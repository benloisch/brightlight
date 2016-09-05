#pragma once

#include "Material.h"
#include "Lambertian.h"

class Matte : public Material
{
public:
	BRDF *ambientBRDF;
	BRDF *diffuseBRDF;

	BRDF* getAmbientBRDF();
	BRDF* getDiffuseBRDF();
	
	Matte();
	~Matte();

};