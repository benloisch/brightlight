#include "RayTracer.h"
//#include "Utilities.h"
#include "Sphere.h"
#include "Point_2D.h"
#include "Plane.h"
#include "Material.h"
#include "Matte.h"
#include "Lambertian.h"
#include <float.h>
#include <iostream>
#include <ctime>
using namespace std;

RayTracer::RayTracer() {

}

void RayTracer::createImage() {
	cout << "Creating BMP..." << endl;
	bmp.createBMP(512, 512, "output");
	cout << "Size of BMP: " << bmp.width << " x " << bmp.height << endl;
	bmp.setInitialBMPColor(0, 0, 0);
}

void RayTracer::setupCamera() {
	cout << "Setting up camera..." << endl;
	cam.setAspectRatio(bmp.width, bmp.height);
	cam.setFieldOfView(90);
	cout << "Camera has " << cam.fieldOfView * (180 / PI) << " degree field of view." << endl;
	cam.setCameraOrigin(0, 3, -5);
	cam.setCameraPointOfInterest(0, 2, 6);
	cam.calculateCameraMatrix();
	cam.setThinLensFocalPlaneDistance(10);
	cam.setThinLensRadius(1);
	cam.setThinLensViewPlaneDistance(1);
}

void RayTracer::setSamples() {
	cout << "Initializing samples..." << endl;
	sample.setNumberOfSamples(16);
	cout << "Rendering with " << sample.numberOfSamples << " samples per pixel." << endl;
	sample.initializeHemisphereSamples();
	sample.setE(2.718281828459);
}

void RayTracer::createGeometricObjects() {
	cout << "Loading geometric objects..." << endl;
	objects.push_back(new Sphere);
	objects[objects.size() - 1]->setOrigin(-4, 2, 2);
	objects[objects.size() - 1]->setColor(200, 100, 0);
	objects[objects.size() - 1]->setRadius(2);

	RGB sphereColor = objects[objects.size() - 1]->getColor();
	Material *mat = new Matte;
	mat->getAmbientBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getAmbientBRDF()->setDiffuseReflectionCoefficient(0.1);
	mat->getDiffuseBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getDiffuseBRDF()->setDiffuseReflectionCoefficient(0.5);
	objects[objects.size() - 1]->setMaterial(mat);

	objects.push_back(new Sphere);
	objects[objects.size() - 1]->setOrigin(0, 2, 5);
	objects[objects.size() - 1]->setColor(0, 100, 220);
	objects[objects.size() - 1]->setRadius(2);

	sphereColor = objects[objects.size() - 1]->getColor();
	mat = new Matte;
	mat->getAmbientBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getAmbientBRDF()->setDiffuseReflectionCoefficient(0.1);
	mat->getDiffuseBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getDiffuseBRDF()->setDiffuseReflectionCoefficient(0.5);
	objects[objects.size() - 1]->setMaterial(mat);

	objects.push_back(new Sphere);
	objects[objects.size() - 1]->setOrigin(6, 2, 10);
	objects[objects.size() - 1]->setColor(50, 200, 20);
	objects[objects.size() - 1]->setRadius(2);

	sphereColor = objects[objects.size() - 1]->getColor();
	mat = new Matte;
	mat->getAmbientBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getAmbientBRDF()->setDiffuseReflectionCoefficient(0.1);
	mat->getDiffuseBRDF()->setDiffuseColor(sphereColor.r, sphereColor.g, sphereColor.b);
	mat->getDiffuseBRDF()->setDiffuseReflectionCoefficient(0.5);
	objects[objects.size() - 1]->setMaterial(mat);

	objects.push_back(new Plane);
	objects[objects.size() - 1]->setPlaneNormal(0, 1, 0);
	objects[objects.size() - 1]->setColor(200, 200, 220);
	objects[objects.size() - 1]->setPointOnPlane(0, 0, 0);
	objects[objects.size() - 1]->setCheckered(true);

	//create material for plane
	RGB planeColor = objects[objects.size() - 1]->getColor();
	mat = new Matte;
	mat->getAmbientBRDF()->setDiffuseColor(planeColor.r, planeColor.g, planeColor.b);
	mat->getAmbientBRDF()->setDiffuseReflectionCoefficient(0.1);
	mat->getDiffuseBRDF()->setDiffuseColor(planeColor.r, planeColor.g, planeColor.b);
	mat->getDiffuseBRDF()->setDiffuseReflectionCoefficient(0.5);
	objects[objects.size() - 1]->setMaterial(mat);
	
	RaytracingObject* obj = objects[objects.size() - 1];
}

void RayTracer::render() {
	//loop through pixels and shoot rays into scene 

	//create clock variable to record miliseconds of rendering time
	clock_t begin = clock();

	cout << "Rendering image..." << endl;

	for (unsigned int y = 0; y < bmp.height; y++) {
		if (y == 1) { //display time estimate
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			if (elapsed_secs * bmp.height < 60)
				std::cout << "Image will be rendered in approximately " << elapsed_secs * bmp.height << " seconds..." << endl;
			else
				std::cout << "Image will be rendered in approximately " << elapsed_secs * bmp.height / 60 << " minutes..." << endl;
		}
		for (unsigned int x = 0; x < bmp.width; x++) {

			RGB rgb;
			sample.jittered();
			//sample.mapSamplesToDisk();
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

				//material used for shading object that ray intersects
				Material *material = NULL;

				for (unsigned int i = 0; i < objects.size(); i++) {
					objects[i]->intersectRay(depth, primaryRay, rayOrigin);
					if (depth < minDepth) {
						object = objects[i];
						minDepth = depth;
						material = object->getMaterial();
					}
				}

				if (object != NULL) {
					rgb += material->shade();
				}
			}

			rgb /= sample.numberOfSamples;

			//clamp rgb (very crude)
			double maxNum = max(max(rgb.r, rgb.g), rgb.b);
			if (maxNum > 255) {
				rgb /= maxNum;
			}

			bmp.setPixelColor(x, y, (unsigned char)rgb.r, (unsigned char)rgb.g, (unsigned char)rgb.b);
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	if (elapsed_secs < 60)
		std::cout << "Rendered image in: " << elapsed_secs << " seconds." << endl;
	else
		std::cout << "Rendered image in: " << elapsed_secs / 60 << " minutes." << endl;
}

void RayTracer::saveImage() {
	bmp.saveBMP();
}

RayTracer::~RayTracer() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}