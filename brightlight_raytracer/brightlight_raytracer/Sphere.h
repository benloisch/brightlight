#pragma once

#include "RaytracingObject.h"
#include "RGB.h"
#include <float.h>
#include <math.h>

class Sphere : public RaytracingObject{

public:

	double radius;
	double xOrigin;
	double yOrigin;
	double zOrigin;
	RGB rgb;

	Sphere();
	void setRadius(double r);
	void setOrigin(double x, double y, double z);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	inline 
	RGB Sphere::getColor() {
		return rgb;
	};
	inline
	void Sphere::intersectRay(double &depth, Vector rayIn, Camera cam) {
		Vector sphereOrigin(xOrigin, yOrigin, zOrigin, 0);

		double a = rayIn * rayIn;
		double b = ((cam.cameraOrigin - sphereOrigin) * rayIn) * 2;
		double c = ((cam.cameraOrigin - sphereOrigin) * (cam.cameraOrigin - sphereOrigin)) - (radius * radius);

		double discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0) {
			depth = DBL_MAX;
			return;
		}

		double t1 = (-b + sqrt(((b * b) - (4 * a * c)))) / (2 * a);
		double t2 = (-b - sqrt(((b * b) - (4 * a * c)))) / (2 * a);

		depth = (t1 < t2) ? t1 : t2;
		if (depth <= 0) {
			depth = DBL_MAX;
			return;
		}

		//depth gets returned through parameter
	}
};