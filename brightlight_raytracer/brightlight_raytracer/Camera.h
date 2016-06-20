#pragma once

#include "matrix.h"
#include "Vector.h"
using namespace blmatrix;
using namespace blvector;

class Camera {
public:

	Matrix cameraMatrix;
	Vector cameraOrigin;
	Vector cameraPOI; //camera point of interest

	Camera();
	void setCameraOrigin(double x, double y, double z);
	void setCameraPointOfInterest(double x, double y, double z);
	void calculateCameraMatrix();

};