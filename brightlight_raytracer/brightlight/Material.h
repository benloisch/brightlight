#pragma once

#include <iostream>
#include "BRDF.h"
#include <vector>

using namespace std;

class RaytracingObject;

class Material
{
public:

	//methods for Matte class
	virtual BRDF* getAmbientBRDF() { return NULL; } //get Matte's ambient BRDF to set its values
	virtual BRDF* getDiffuseBRDF() { return NULL; } //get Matte's diffuse BRDF to set its values
	virtual BRDF* getSpecularBRDF() { return NULL; } //get Phong's specular BRDF to set its values
};