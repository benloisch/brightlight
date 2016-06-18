#include "Camera.h"
#include "Vector.h"
using namespace blvector;

Camera::Camera() {
	
}

Camera::Camera(double x, double y, double z, double xLook, double yLook, double zLook) {
	cameraOrigin.x = x;
	cameraOrigin.y = y;
	cameraOrigin.z = z;
	cameraOrigin.w = 0;
	
	//create camera matrix
	Vector vOrigin(x, y, z, 0);
	Vector vLook(xLook, yLook, zLook, 0);
	Vector vUp(0, 1, 0, 0);

	Vector vForward = vLook - vOrigin;
	vForward.normalize();
	
	Vector vRight = vUp ^ vForward;
	vRight.normalize();

	vUp = vForward ^ vRight;
	vUp.normalize();


	cameraMatrix.setRow1(vRight.x, vRight.y, vRight.z, 0);
	cameraMatrix.setRow2(vUp.x, vUp.y, vUp.z, 0);
	cameraMatrix.setRow3(vForward.x, vForward.y, vForward.z, 0);
	cameraMatrix.setRow4(vOrigin.x, vOrigin.y, vOrigin.z, 1);
}