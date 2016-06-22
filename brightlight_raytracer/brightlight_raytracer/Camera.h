#pragma once

#include "matrix.h"
#include "Vector.h"
#include "Camera.h"
#include "ImageBMP.h"
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

	inline Vector pinholeCamera(unsigned int x, unsigned int y, double sx, double sy, Camera& cam, ImageBMP& bmp, Vector& rayOrigin) {
		double samplex = sx + x;
		double sampley = sy + y;

		//convert from raster space to normalized device coordinate space

		double xPixelNDC = samplex / bmp.width;
		double yPixelNDC = sampley / bmp.height;

		//convert from NDC space to screen space
		double xPixelScreen = ((2 * xPixelNDC) - 1) * cam.aspectRatio * tan(cam.fieldOfView / 2);
		double yPixelScreen = 1 - (2 * yPixelNDC) * tan(cam.fieldOfView / 2);

		Vector primaryRay(xPixelScreen, yPixelScreen, 1, 0);
		primaryRay.normalize();

		rayOrigin.x = cam.cameraMatrix.m[3][0];
		rayOrigin.y = cam.cameraMatrix.m[3][1];
		rayOrigin.z = cam.cameraMatrix.m[3][2];

		return primaryRay;
	}

	inline Vector thinlensCamera(unsigned int x, unsigned int y, double sx, double sy, double cx, double cy, Camera& cam, ImageBMP& bmp, Vector& rayOrigin) {
		double samplex = sx + x;
		double sampley = sy + y;

		//convert from raster space to normalized device coordinate space

		double xPixelNDC = samplex / bmp.width;
		double yPixelNDC = sampley / bmp.height;

		//convert from NDC space to screen space
		double xPixelScreen = ((2 * xPixelNDC) - 1) * cam.aspectRatio * tan(cam.fieldOfView / 2);
		double yPixelScreen = 1 - (2 * yPixelNDC) * tan(cam.fieldOfView / 2);

		double f = 10;
		double d = 1;

		double px = xPixelScreen * (f / d);
		double py = yPixelScreen * (f / d);

		//Vector p(xPixelScreen * (f / d), yPixelScreen * (f / d), f, 0);
		//Vector ls(cx, cy, d, 0);
		Vector bx(cam.cameraMatrix.m[0][0], cam.cameraMatrix.m[0][1], cam.cameraMatrix.m[0][2], 0);
		Vector by(cam.cameraMatrix.m[1][0], cam.cameraMatrix.m[1][1], cam.cameraMatrix.m[1][2], 0);
		Vector bz(cam.cameraMatrix.m[2][0], cam.cameraMatrix.m[2][1], cam.cameraMatrix.m[2][2], 0);
		
		Vector primaryRay = (bx * (px - cx)) + (by * (py - cy)) + (bz * f);
		primaryRay.normalize();

		rayOrigin = cam.cameraOrigin + (bx * cx) + (by * cy) + bz;

		return primaryRay;
	}

};