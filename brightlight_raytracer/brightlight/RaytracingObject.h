#pragma once

#include "Camera.h"
#include "RGB.h"
#include "Vector.h"
#include "Material.h"
#include <string>

using namespace std;
using namespace blvector;

class Material;

class RaytracingObject {

public:

	inline virtual void intersectRay(double &depth, Vector rayIn, Vector rayOrigin) = 0;
	inline virtual void setColor(double r, double g, double b) = 0;
	inline virtual RGB getColor() = 0;
	inline virtual Vector getNormal() = 0;
	inline virtual string getTag() = 0;
	inline virtual void setTag(string s) = 0;

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
	virtual void setPlaneMatrix(double rotation) {};
	virtual void setPlaneWidthHeight(double w, double h) {};
};