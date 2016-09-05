#pragma once

#include "RaytracingObject.h"
#include <float.h>
#include <math.h>
#include "Vector.h"
#include "Material.h"
using namespace blvector;

class Plane : public RaytracingObject{

public:

	string tag;
	Vector pointOnPlane;
	Vector planeNormal;
	RGB rgb;
	RGB temprgb;
	bool checkered;
	Material *material;

	double width;
	double height;
	Matrix planeMatrix;

	Plane();
	~Plane();

	inline void setTag(string s) {
		tag = s;
	}

	inline string getTag() {
		return tag;
	}

	inline Vector getNormal() {
		return planeNormal;
	}
	Material* getMaterial();
	void setMaterial(Material* mat);
	void setCheckered(bool setFlag);
	void setPlaneMatrix(double rotation);
	void setPlaneWidthHeight(double w, double h);
	void setPointOnPlane(double x, double y, double z);
	void setPlaneNormal(double x, double y, double z);
	inline void Plane::setColor(double r, double g, double b) {
		rgb.r = r;
		rgb.g = g;
		rgb.b = b;

		temprgb = rgb;
	}
	inline RGB getColor() {
		return rgb;
	}

	inline virtual void intersectRay(double &depth, Vector rayIn, Vector rayOrigin) {

		depth = ((pointOnPlane - rayOrigin) * planeNormal) / (rayIn * planeNormal);

		Vector p = (rayIn * depth) + rayOrigin;
		p.w = 1;

		Matrix inv = planeMatrix.inverse();
		
		double testX = abs((p * inv).x);
		double testY = abs((p * inv).y);

		if (depth <= 0) {
			depth = DBL_MAX;
			return;
		}

		if (testX > width || testY > height) {
			depth = DBL_MAX;
			return;
		}

		//depth gets returned through parameter
	
		double testXCheckered = (p * inv).x;
		double testYCheckered = (p * inv).y;

		//if checkered is true, adjust rgb to be black or white depending on divisibility by 2
		if (checkered) {
			
			if (testXCheckered < 0)
				testXCheckered -= 1;

			if (testYCheckered < 0)
				testYCheckered -= 1;

			if (((abs(int(testXCheckered)) % 2 == 0) && (abs(int(testYCheckered)) % 2 == 0)) || ((abs(int(testXCheckered)) % 2 == 1) && (abs(int(testYCheckered)) % 2 == 1))) {
				rgb.r = 0;
				rgb.g = 0;
				rgb.b = 0;
			}
			else {
				rgb = temprgb;
			}
		}
	}


};