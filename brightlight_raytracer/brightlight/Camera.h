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
	double thinlensRadius;
	double thinlensViewPlaneDistance;
	double thinlensFocalPlaneDistance;

	Camera();
	void setThinLensViewPlaneDistance(double d);
	void setThinLensFocalPlaneDistance(double d);
	void setThinLensRadius(double r);
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
		primaryRay = primaryRay * cam.cameraMatrix;
		primaryRay.normalize();

		rayOrigin = cam.cameraOrigin;

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

		double f = thinlensFocalPlaneDistance;
		double d = thinlensViewPlaneDistance;

		double px = xPixelScreen * (f / d);
		double py = yPixelScreen * (f / d);

		cx *= thinlensRadius;
		cy *= thinlensRadius;

		//Vector p(xPixelScreen * (f / d), yPixelScreen * (f / d), f, 0);
		//Vector ls(cx, cy, d, 0);
		Vector bx(cam.cameraMatrix.m[0][0], cam.cameraMatrix.m[0][1], cam.cameraMatrix.m[0][2], 0);
		Vector by(cam.cameraMatrix.m[1][0], cam.cameraMatrix.m[1][1], cam.cameraMatrix.m[1][2], 0);
		Vector bz(cam.cameraMatrix.m[2][0], cam.cameraMatrix.m[2][1], cam.cameraMatrix.m[2][2], 0);

		Vector primaryRay = (bx * (px - cx)) + (by * (py - cy)) + (bz * f);
		primaryRay.normalize();

		rayOrigin = cam.cameraOrigin + (bx * cx) + (by * cy);

		return primaryRay;
	}

};