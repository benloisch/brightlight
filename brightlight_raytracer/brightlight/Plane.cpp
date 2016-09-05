#include "Plane.h"

Plane::Plane() {
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;

	tag = "none";

	material = NULL;
}

Plane::~Plane() {
	delete material;
}

void Plane::setPlaneMatrix(double rotation) {
	Vector right;
	Vector up;

	if ((planeNormal.x == 0 && planeNormal.y == 1 && planeNormal.z == 0) || (planeNormal.x == 0 && planeNormal.y == -1 && planeNormal.z == 0)){
		right.x = 1;
	}
	else {
		right = Vector(0, 1, 0, 0) ^ planeNormal;
	}

	Matrix rotateRightAxis;
	rotateRightAxis.setRotArb(planeNormal.x, planeNormal.y, planeNormal.z, rotation);

	right = right * rotateRightAxis;

	up = planeNormal ^ right;

	planeMatrix.setRow1(right.x, right.y, right.z, 0);
	planeMatrix.setRow2(up.x, up.y, up.z, 0);
	planeMatrix.setRow3(planeNormal.x, planeNormal.y, planeNormal.z, 0);
	planeMatrix.setRow4(pointOnPlane.x, pointOnPlane.y, pointOnPlane.z, 1);
}

void Plane::setPlaneWidthHeight(double w, double h) {
	width = w;
	height = h;
}

void Plane::setMaterial(Material* mat) {
	material = mat;
};

Material* Plane::getMaterial() {
	return material;
}

void Plane::setCheckered(bool setFlag) {
	checkered = setFlag;
}

void Plane::setPlaneNormal(double x, double y, double z) {
	planeNormal.x = x;
	planeNormal.y = y;
	planeNormal.z = z;
	planeNormal.normalize();
}

void Plane::setPointOnPlane(double x, double y, double z) {
	pointOnPlane.x = x;
	pointOnPlane.y = y;
	pointOnPlane.z = z;
}