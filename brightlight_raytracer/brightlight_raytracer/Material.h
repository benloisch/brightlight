#pragma once

#include <iostream>
#include "RGB.h"
#include "BRDF.h"
#include "Light.h"
#include <vector>

using namespace std;

class Material
{
public:
	virtual RGB shade(Shade s, vector<Light*> ambient, vector<Light*> directional, vector<Light*> point) = 0;

	//methods for Matte class
	virtual BRDF* getAmbientBRDF() { return NULL; } //get Matte's ambient BRDF to set its values
	virtual BRDF* getDiffuseBRDF() { return NULL; } //get Matte's diffuse BRDF to set its values
};