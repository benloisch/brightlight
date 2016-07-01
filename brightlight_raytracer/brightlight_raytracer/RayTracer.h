#pragma once
#include "RaytracingObject.h"
#include "ImageBMP.h"
#include "Camera.h"
#include "Sample.h"
#include "Light.h"
#include <vector>
using namespace std;

class RayTracer {

public:


	Camera cam;
	ImageBMP bmp;
	vector<RaytracingObject*> objects;
	Sample sample;
	vector<Light*> ambientLight;
	vector<Light*> directionalLights;
	vector<Light*> pointLights;

	RayTracer();
	~RayTracer();

	void createImage();
	void setupCamera();
	void setSamples();
	void setupLights();
	void createGeometricObjects();
	void render();
	void saveImage();

};