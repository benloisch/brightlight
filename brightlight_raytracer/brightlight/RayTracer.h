#pragma once
#include "RaytracingObject.h"
#include "ImageBMP.h"
#include "Camera.h"
#include "Sample.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "Phong.h"
#include <vector>
#include "Sphere.h"
#include "Point_2D.h"
#include "Plane.h"
#include "Material.h"
#include "Matte.h"
#include "Phong.h"
#include "Lambertian.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "RectangleAreaLight.h"
#include "PointLight.h"
#include "Shade.h"
#include "RGB.h"
#include <float.h>
#include <iostream>
#include <ctime>

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
	vector<Light*> rectangleAreaLights;

	RayTracer();
	~RayTracer();

	Material *createPhongMaterial(double ambientCoefficient, double diffuseCoefficient, double specularCoefficient, double phongExponent);
	Material *createMatteMaterial(double ambientCoefficient, double diffuseCoefficient);

	void createPlane(Material *mat, vector<RaytracingObject*> &objects, double w, double h, double degreeRotation, double r, double g, double b, double nx, double ny, double nz, double px, double py, double pz, bool checkered, string tag = "none");
	void createSphere(Material *mat, vector<RaytracingObject*> &objects, double r, double g, double b, double ox, double oy, double oz, double radius, string tag = "none");

	void createRectangleAreaLight(vector<Light*> &light, double originx, double originy, double originz, double width, double height, int samplePointWidth, double radianRotation, double r, double g, double b, double x, double y, double z, double i);
	void createDirectionalLight(vector<Light*> &light, double r, double g, double b, double x, double y, double z, double i);
	void createAmbientLight(vector<Light*> &light, double r, double g, double b, double i);
	void createAreaPointLight(vector<Light*> &light, double radius, int samplePointAmount, double r, double g, double b, double x, double y, double z, double i);

	void createImage();
	void setupCamera();
	void setSamples();
	void setupLights();
	void createGeometricObjects();
	void render();
	void saveImage();

};