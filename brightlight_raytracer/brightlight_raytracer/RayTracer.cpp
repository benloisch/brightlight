#include "RayTracer.h"
#include "Utilities.h"
#include <float.h>
#include <iostream>
#include <ctime>
using namespace std;

void RayTracer::createGeometricObjects() {
	objects.push_back(new Sphere(3, 0, 1, 6));
	objects[objects.size() - 1]->setColor(255, 0, 0);

}

void RayTracer::render() {
	//loop through pixels and shoot rays into scene 

	//create clock variable to record miliseconds of rendering time
	clock_t begin = clock();

	double aspectRatio = double(bmp.width) / double(bmp.height);
	double fov = 90;
	//convert fov from degrees to radians
	fov = (3.14159265359 * fov) / 180.0;

	for (unsigned int y = 0; y < bmp.height + 1; y++) {
		for (unsigned int x = 0; x < bmp.width; x++) {
			//convert from raster space to normalized device coordinate space
			//double xPixelNDC = (x + 0.5) / bmp.width;
			//double yPixelNDC = (y + 0.5) / bmp.height;

			//convert from NDC space to screen space
			//double xPixelScreen = ((2 * xPixelNDC) - 1) * aspectRatio * tan(fov / 2);
			//double yPixelScreen = 1 - (2 * yPixelNDC);

			//Vector primaryRay(xPixelScreen, yPixelScreen, 1, 0);
			//primaryRay.normalize();

			//find closest object
			//RaytracingObject *object = NULL;
			//double minDepth = DBL_MAX;
			//double depth = DBL_MAX;
			
			//for (unsigned int i = 0; i < objects.size(); i++) {
			//	objects[i]->intersectRay(depth, primaryRay, cam);
			//	if (depth < minDepth) {
			//		object = objects[i];
			//	}
			//}

			//RGB rgb = bmp.getPixel(x, y);

			//if (object != NULL) {
			//	rgb = object->getColor();
			//}

			bmp.setPixel(x, y, 0, 0, 0);
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Rendered image in: " << elapsed_secs * 1000 << " miliseconds." << endl;
}

int RayTracer::saveImage() {
	if (!bmp.saveBMP()) {
		cout << "Failed to save bmp file" << endl;
		return -1;
	}
	else {
		return 0;
	}
}

RayTracer::~RayTracer() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}