#pragma once
#include "RaytracingObject.h"
#include "Sphere.h"
#include "ImageBMP.h"
#include "Camera.h"
#include <vector>
using namespace std;

class RayTracer {

public:


	Camera cam;
	ImageBMP bmp;
	vector<RaytracingObject*> objects;

	RayTracer() : cam(0, 1, -1, 0, 1, 1), bmp(512, 512, "image") {
		bmp.setInitialBMPColor(255, 255, 255);
	}
	~RayTracer();

	void createGeometricObjects();
	void render();
	int saveImage();

};