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
	Material *material;
	Vector storedNormal;
	string tag;

	Sphere();
	~Sphere();

	inline void setTag(string s) {
		tag = s;
	}

	inline string getTag() {
		return tag;
	}

	inline Vector getNormal() {
		return storedNormal;
	}
	Material* getMaterial();
	void setMaterial(Material* mat);
	void setRadius(double r);
	void setOrigin(double x, double y, double z);
	void setColor(double r, double g, double b);
	inline 
	RGB Sphere::getColor() {
		return rgb;
	};
	inline
		void Sphere::intersectRay(double &depth, Vector rayIn, Vector rayOrigin) {
		Vector sphereOrigin(xOrigin, yOrigin, zOrigin, 0);

		double a = rayIn * rayIn;
		double b = ((rayOrigin - sphereOrigin) * rayIn) * 2;
		double c = ((rayOrigin - sphereOrigin) * (rayOrigin - sphereOrigin)) - (radius * radius);

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
		//set normal at currect intersection point before leaving function
		storedNormal = (rayOrigin + (rayIn * depth)) - Vector(xOrigin, yOrigin, zOrigin, 0);
		storedNormal.normalize();
	}
};