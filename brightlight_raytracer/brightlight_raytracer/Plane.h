#pragma once

#include "RaytracingObject.h"
#include <float.h>
#include "Vector.h"
using namespace blvector;

class Plane : public RaytracingObject{

public:

	Vector pointOnPlane;
	Vector planeNormal;
	RGB rgb;
	bool checkered;

	Plane();

	void setCheckered(bool setFlag);
	void setPointOnPlane(double x, double y, double z);
	void setPlaneNormal(double x, double y, double z);
	inline void Plane::setColor(unsigned char r, unsigned char g, unsigned char b) {
		rgb.r = r;
		rgb.g = g;
		rgb.b = b;
	}
	inline RGB getColor() {
		return rgb;
	}

	inline virtual void intersectRay(double &depth, Vector rayIn, Vector rayOrigin) {

		depth = ((pointOnPlane - rayOrigin) * planeNormal) / (rayIn * planeNormal);

		if (depth <= 0) {
			depth = DBL_MAX;
			return;
		}

		//depth gets returned through parameter
	
		//if checkered is true, adjust rgb to be black or white depending on divisibility by one or zero
		if (checkered) {
			double magnitude = (((rayIn * depth) + rayOrigin) - pointOnPlane).getMagnitude();
			if (int(magnitude) % 2 == 0) {
				rgb.r = 0;
				rgb.g = 0;
				rgb.b = 0;
			}
			else {
				rgb.r = 255;
				rgb.g = 255;
				rgb.b = 255;
			}
		}
	}


};