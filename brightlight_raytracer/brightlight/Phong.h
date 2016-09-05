#pragma once

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong : public Material
{
public:
	BRDF *ambientBRDF;
	BRDF *diffuseBRDF;
	BRDF *specularBRDF;

	BRDF* getAmbientBRDF();
	BRDF* getDiffuseBRDF();
	BRDF* getSpecularBRDF();
	
	Phong();
	~Phong();

};