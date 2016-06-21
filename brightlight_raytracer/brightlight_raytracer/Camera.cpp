#include "Camera.h"
#include "Vector.h"
using namespace blvector;

Camera::Camera() {
	aspectRatio = 0;
	fieldOfView = 0;
}

void Camera::setAspectRatio(const unsigned int w, const unsigned int h) {
	aspectRatio = double(w) / double(h);
}

void Camera::setFieldOfView(double degrees) {
	//convert fov from degrees to radians
	fieldOfView = (3.14159265359 * degrees) / 180.0;
}

void Camera::setCameraPointOfInterest(double x, double y, double z) { //the point at which the camera looks at
	cameraPOI.x = x;
	cameraPOI.y = y;
	cameraPOI.z = z;
}

void Camera::setCameraOrigin(double x, double y, double z) {
	cameraOrigin.x = x;
	cameraOrigin.y = y;
	cameraOrigin.z = z;
}

void Camera::calculateCameraMatrix() {
	
	//create camera matrix
	Vector vUp(0, 1, 0, 0); //use world up (y axis) as a reference
	
	Vector vForward = cameraPOI - cameraOrigin; //create z axis basic vector
	vForward.normalize();
	
	Vector vRight = vUp ^ vForward; //create x axis basis vector
	vRight.normalize();

	vUp = vForward ^ vRight; //last, create y axis basic vector
	vUp.normalize();

	//create matrix
	cameraMatrix.setRow1(vRight.x, vRight.y, vRight.z, 0);
	cameraMatrix.setRow2(vUp.x, vUp.y, vUp.z, 0);
	cameraMatrix.setRow3(vForward.x, vForward.y, vForward.z, 0);
	cameraMatrix.setRow4(cameraOrigin.x, cameraOrigin.y, cameraOrigin.z, 1);
}