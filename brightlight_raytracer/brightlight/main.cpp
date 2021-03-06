#include <iostream>
#include "RayTracer.h"

using namespace std;

/*
Author: Ben Loisch
Version: 0.1
Date Started: 06/07/2016
Date Modified: 06/30/2016
Ray Tracer #3
*/

int main() {

	cout << "Initializing ray tracer..." << endl;

	try {
		RayTracer raytracer;
		raytracer.createImage();
		raytracer.setupCamera();
		raytracer.setSamples();
		raytracer.setupLights();
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