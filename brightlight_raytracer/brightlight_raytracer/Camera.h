#pragma once

#include "matrix.h"
#include "Vector.h"
using namespace blmatrix;
using namespace blvector;

class Camera {
public:

	Matrix cameraMatrix;
	Vector cameraOrigin;

	Camera();
	Camera(double x, double y, double z, double xLook, double yLook, double zLook);

};