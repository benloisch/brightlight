#pragma once

#include "matrix.h"
#include "Vector.h"
using namespace blmatrix;
using namespace blvector;

class Camera {
public:

	Matrix cameraMatrix; //used in vector * matrix transformation for shooting rays
	Vector cameraOrigin;
	Vector cameraPOI; //at what point the camera will look at or focus on

	double aspectRatio;
	double fieldOfView;

	Camera();
	void setAspectRatio(const unsigned int w, const unsigned int h);
	void setFieldOfView(double degrees);
	void setCameraOrigin(double x, double y, double z);
	void setCameraPointOfInterest(double x, double y, double z);
	void calculateCameraMatrix();

};