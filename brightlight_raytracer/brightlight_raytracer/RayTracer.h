#pragma once
#include "RaytracingObject.h"
#include "ImageBMP.h"
#include "Camera.h"
#include "Sample.h"
#include <vector>
using namespace std;

class RayTracer {

public:


	Camera cam;
	ImageBMP bmp;
	vector<RaytracingObject*> objects;
	Sample sample;

	RayTracer();
	~RayTracer();

	void createImage();
	void setupCamera();
	void setSamples();
	void createGeometricObjects();
	void render();
	void saveImage();

};