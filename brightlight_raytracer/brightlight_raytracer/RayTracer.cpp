#include "RayTracer.h"
#include "Utilities.h"
#include "Sphere.h"
#include "Point_2D.h"
#include "Plane.h"
#include <float.h>
#include <iostream>
#include <ctime>
using namespace std;

RayTracer::RayTracer() {

}

void RayTracer::createImage() {
	bmp.createBMP(512, 512, "output");
	bmp.setInitialBMPColor(0, 0, 0);
}

void RayTracer::setupCamera() {
	cam.setAspectRatio(bmp.width, bmp.height);
	cam.setFieldOfView(90);
	cam.setCameraOrigin(0, 5, 0);
	cam.setCameraPointOfInterest(0, 3, 6);
	cam.calculateCameraMatrix();
}

void RayTracer::setSamples() {
	sample.setNumberOfSamples(16);
	sample.initializeHemisphereSamples();
	sample.setE(2.718281828459);
}

void RayTracer::createGeometricObjects() {
	objects.push_back(new Sphere);
	((Sphere*)objects[objects.size() - 1])->setOrigin(0, 1, 12);
	((Sphere*)objects[objects.size() - 1])->setColor(200, 100, 0);
	((Sphere*)objects[objects.size() - 1])->setRadius(3);

	objects.push_back(new Sphere);
	((Sphere*)objects[objects.size() - 1])->setOrigin(2, 1, 10);
	((Sphere*)objects[objects.size() - 1])->setColor(0, 100, 220);
	((Sphere*)objects[objects.size() - 1])->setRadius(3);

	objects.push_back(new Plane);
	((Plane*)objects[objects.size() - 1])->setPlaneNormal(0, 1, 0);
	((Plane*)objects[objects.size() - 1])->setColor(200, 200, 220);
	((Plane*)objects[objects.size() - 1])->setPointOnPlane(0, 0, 0);
	((Plane*)objects[objects.size() - 1])->setCheckered(true);

}

void RayTracer::render() {
	//loop through pixels and shoot rays into scene 

	//create clock variable to record miliseconds of rendering time
	clock_t begin = clock();

	for (unsigned int y = 0; y < bmp.height; y++) {
		//cout << y << endl;
		for (unsigned int x = 0; x < bmp.width; x++) {

			RGB rgb;
			sample.jittered();
			sample.mapSamplesToDisk();
			//sample.mapDiskToHemisphere();

			//for (int j = 0; j < sample.numberOfSamples; j++) {
			//	cout << "x: " << sample.samples[j].x << endl;
			//	cout << "y: " << sample.samples[j].y << endl;
			//}

			//sample the image
			for (unsigned int i = 0; i < sample.numberOfSamples; i++) {
				//bmp.setPixelColor(sample.samples[i].x * bmp.width, sample.samples[i].y * bmp.width, 20, 200, 20);
				//bmp.setPixelColor(sample.diskSamples[i].x * bmp.width, sample.diskSamples[i].y * bmp.width, 20, 200, 20);
				//bmp.setPixelColor(sample.hemisphereSamples[i].x * bmp.width, sample.hemisphereSamples[i].y * bmp.width, 20, sample.hemisphereSamples[i].z * 255, 20);

				Vector rayOrigin;
				//Vector primaryRay = cam.pinholeCamera(x, y, sample.samples[i].x, sample.samples[i].y, cam, bmp, rayOrigin);
				Vector primaryRay = cam.thinlensCamera(x, y, sample.samples[i].x, sample.samples[i].y, sample.diskSamples[i].x, sample.diskSamples[i].y, cam, bmp, rayOrigin);

				//find closest object
				RaytracingObject *object = NULL;
				double minDepth = DBL_MAX;
				double depth = DBL_MAX;

				for (unsigned int i = 0; i < objects.size(); i++) {
					objects[i]->intersectRay(depth, primaryRay, rayOrigin);
					if (depth < minDepth) {
						object = objects[i];
						minDepth = depth;
					}
				}

				if (object != NULL) {
					rgb += object->getColor();
				}
			}

			rgb /= sample.numberOfSamples;
			bmp.setPixelColor(x, y, rgb.r, rgb.g, rgb.b);
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Rendered image in: " << elapsed_secs * 1000 << " miliseconds." << endl;
}

void RayTracer::saveImage() {
	bmp.saveBMP();
}

RayTracer::~RayTracer() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}