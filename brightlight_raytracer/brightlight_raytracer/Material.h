#pragma once

#include <iostream>
#include "RGB.h"
#include "BRDF.h"

class Material
{
public:
	virtual RGB shade() = 0;

	//methods for Matte class
	virtual BRDF* getAmbientBRDF() { return NULL; } //get Matte's ambient BRDF to set its values
	virtual BRDF* getDiffuseBRDF() { return NULL; } //get Matte's diffuse BRDF to set its values
};