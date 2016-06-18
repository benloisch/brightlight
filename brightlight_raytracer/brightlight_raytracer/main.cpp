#include <iostream>
#include "RayTracer.h"

using namespace std;

/*
Author: Ben Loisch
Version: 0.1
Date Started: 06/07/2016
Date Modified: 06/18/2016
Ray Tracer #3


*/

int main() {

	RayTracer raytracer;
	raytracer.createGeometricObjects();
	raytracer.render();
	raytracer.saveImage();
	
	system("PAUSE");

	return 0;
}