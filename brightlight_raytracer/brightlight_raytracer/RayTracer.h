#pragma once
#include "RaytracingObject.h"
#include "ImageBMP.h"
#include "Camera.h"
#include <vector>
using namespace std;

class RayTracer {

public:


	Camera cam;
	ImageBMP bmp;
	vector<RaytracingObject*> objects;

	RayTracer();
	~RayTracer();

	void createImage();
	void setupCamera();
	void createGeometricObjects();
	void render();
	void saveImage();

};