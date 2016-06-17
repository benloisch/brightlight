#pragma once

#include "Camera.h"
#include "RGB.h"
#include "Vector.h"

using namespace blvector;

class RaytracingObject {

public:

	virtual void intersectRay(double &depth, Vector rayIn, Camera cam);
	virtual void setColor(unsigned char r, unsigned char g, unsigned char b);
	virtual RGB getColor();

};