#pragma once

#include "Camera.h"
#include "RGB.h"
#include "Vector.h"
#include "Material.h"

using namespace blvector;

class RaytracingObject {

public:

	inline virtual void intersectRay(double &depth, Vector rayIn, Vector rayOrigin) = 0;
	inline virtual void setColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	inline virtual RGB getColor() = 0;

	//methods for materials
	virtual void setMaterial(Material* mat) {};
	virtual Material* getMaterial() = 0;

	//methods for sphere class
	virtual void setRadius(double r) {};
	virtual void setOrigin(double x, double y, double z) {};

	//methods for plane class
	virtual void setCheckered(bool setFlag) {};
	virtual void setPointOnPlane(double x, double y, double z) {};
	virtual void setPlaneNormal(double x, double y, double z) {};
};