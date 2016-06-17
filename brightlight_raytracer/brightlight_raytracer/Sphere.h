#pragma once

#include "RaytracingObject.h"
#include "RGB.h"

class Sphere : public RaytracingObject{

public:

	double radius;
	double xOrigin;
	double yOrigin;
	double zOrigin;
	RGB rgb;

	Sphere(double radius, double xOrigin, double yOrigin, double zOrigin);

	void setColor(unsigned char r, unsigned char g, unsigned char b);
	RGB getColor();
	void intersectRay(double &depth, Vector rayIn, Camera cam);

};