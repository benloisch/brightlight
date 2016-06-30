#include <iostream>
#include "RayTracer.h"

using namespace std;

/*
Author: Ben Loisch
Version: 0.1
Date Started: 06/07/2016
Date Modified: 06/29/2016
Ray Tracer #3


*/

/*
brdf class
subclass: lambertian
subclass: specular
subclass: glossy

shader class
holds and computes values from materials 	and brdfs

material class
subclass: matte: holds ambient and lambert brdf
subclass: phong: holds ambient, lambert, specular brdf

light class:
subclass: ambient
subclass: directional
subclass: point light
*/


int main() {

	cout << "Initializing ray tracer..." << endl;

	try {
		RayTracer raytracer;
		raytracer.createImage();
		raytracer.setupCamera();
		raytracer.setSamples();
		raytracer.createGeometricObjects();
		raytracer.render();
		raytracer.saveImage();
	}
	catch (const exception e) {
		cout << e.what() << endl;
	}

	system("PAUSE");

	return 0;
}