#include "Plane.h"

Plane::Plane() {
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
}

void Plane::setCheckered(bool setFlag) {
	checkered = setFlag;
}

void Plane::setPlaneNormal(double x, double y, double z) {
	planeNormal.x = x;
	planeNormal.y = y;
	planeNormal.z = z;
}

void Plane::setPointOnPlane(double x, double y, double z) {
	pointOnPlane.x = x;
	pointOnPlane.y = y;
	pointOnPlane.z = z;
}