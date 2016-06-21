#pragma once

#include "Camera.h"
#include "RGB.h"
#include "Vector.h"

using namespace blvector;

class RaytracingObject {

public:

	inline virtual void intersectRay(double &depth, Vector rayIn, Camera cam) = 0;
	inline virtual void setColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	inline virtual RGB getColor() = 0;

};