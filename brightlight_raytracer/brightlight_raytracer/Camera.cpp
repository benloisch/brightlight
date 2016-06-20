#include "Camera.h"
#include "Vector.h"
using namespace blvector;

Camera::Camera() {
	
}

void Camera::setCameraPointOfInterest(double x, double y, double z) {
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
	Vector vUp(0, 1, 0, 0);

	Vector vForward = cameraPOI - cameraOrigin;
	vForward.normalize();
	
	Vector vRight = vUp ^ vForward;
	vRight.normalize();

	vUp = vForward ^ vRight;
	vUp.normalize();

	cameraMatrix.setRow1(vRight.x, vRight.y, vRight.z, 0);
	cameraMatrix.setRow2(vUp.x, vUp.y, vUp.z, 0);
	cameraMatrix.setRow3(vForward.x, vForward.y, vForward.z, 0);
	cameraMatrix.setRow4(cameraOrigin.x, cameraOrigin.y, cameraOrigin.z, 1);
}