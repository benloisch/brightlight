#include "RayTracer.h"

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
	cam.setCameraOrigin(0, 10, -4);
	cam.setCameraPointOfInterest(0, 5, 20);
	cam.calculateCameraMatrix();
	cam.setThinLensFocalPlaneDistance(12);
	cam.setThinLensRadius(1);
	cam.setThinLensViewPlaneDistance(1);
}

void RayTracer::setSamples() {
	cout << "Initializing samples..." << endl;
	sample.setNumberOfSamples(9);
	sample.setNumberOfHemisphereSamples(16);
	sample.setAmbientAmountToShade(0);
	sample.setRoomDepth(5);
	cout << "Setting ambient room depth to " << sample.roomDepth << endl;
	cout << "Rendering with " << sample.numberOfSamples << " samples per pixel." << endl;
	cout << "Rendering with " << sample.numberOfHemisphereSamples << " hemisphere samples per pixel." << endl;
	sample.initializeHemisphereSamples();
	sample.setE(1);// 2.718281828459 = e, e = 1 = even distribution appearing from the top
}

Material *RayTracer::createPhongMaterial(double ambientCoefficient, double diffuseCoefficient, double specularCoefficient, double phongExponent) {
	Material *mat = new Phong;
	mat->getAmbientBRDF()->setReflectionCoefficient(ambientCoefficient);
	mat->getDiffuseBRDF()->setReflectionCoefficient(diffuseCoefficient);
	mat->getSpecularBRDF()->setReflectionCoefficient(specularCoefficient);
	mat->getSpecularBRDF()->setPhongExponent(phongExponent);
	return mat;
}

Material *RayTracer::createMatteMaterial(double ambientCoefficient, double diffuseCoefficient) {
	Material *mat = new Matte;
	mat->getAmbientBRDF()->setReflectionCoefficient(ambientCoefficient);
	mat->getDiffuseBRDF()->setReflectionCoefficient(diffuseCoefficient);
	return mat;
}

void RayTracer::setupLights() {

	cout << "Creating lights..." << endl;
	createAmbientLight(ambientLight, 1, 1, 1, 1);
	//createAreaPointLight(pointLights, 1.5, 4, 1, 1, 1, 2, 12, 10, 2.5);
	createRectangleAreaLight(rectangleAreaLights, 0, 15, 10, 3, 3, 36, 0, 1, 1, 1, 0, -1, 0, 4);

}

void RayTracer::createRectangleAreaLight(vector<Light*> &light, double originx, double originy, double originz, double width, double height, int samplePointWidth, double degreeRotation, double r, double g, double b, double x, double y, double z, double i) {
	light.push_back(new RectangleAreaLight);
	light[light.size() - 1]->setLightColor(r, g, b);
	light[light.size() - 1]->setRadianceScalingFactor(i);
	light[light.size() - 1]->setLightDirection(x, y, z);
	light[light.size() - 1]->setLightOrigin(originx, originy, originz);
	light[light.size() - 1]->setRectangleAreaLightMatrix(degreeRotation);
	light[light.size() - 1]->setRectangleAreaLightWidthHeight(width, height);
	light[light.size() - 1]->setRectangleAreaLightSamplePointAmount(samplePointWidth);

	Material *mat = createMatteMaterial(1, 1);
	createPlane(mat, objects, width, height, degreeRotation, r * 255, g * 255, b * 255, x, y, z, originx, originy, originz, false, "arealight");
}

void RayTracer::createDirectionalLight(vector<Light*> &light, double r, double g, double b, double x, double y, double z, double i) {
	light.push_back(new DirectionalLight);
	light[light.size() - 1]->setLightColor(r, g, b);
	light[light.size() - 1]->setRadianceScalingFactor(i);
	light[light.size() - 1]->setLightDirection(x, y, z);
}

void RayTracer::createAmbientLight(vector<Light*> &light, double r, double g, double b, double i) {
	light.push_back(new AmbientLight);
	light[light.size() - 1]->setLightColor(r, g, b);
	light[light.size() - 1]->setRadianceScalingFactor(i);
}

void RayTracer::createAreaPointLight(vector<Light*> &light, double radius, int samplePointAmount, double r, double g, double b, double x, double y, double z, double i) {
	light.push_back(new PointLight);
	light[light.size() - 1]->setLightColor(r, g, b);
	light[light.size() - 1]->setRadianceScalingFactor(i);
	light[light.size() - 1]->setLightOrigin(x, y, z);
	light[light.size() - 1]->setPointLightRadius(radius);
	light[light.size() - 1]->setAreaPointLightSamplePointAmount(samplePointAmount);
	
	Material *mat = createMatteMaterial(1, 1);
	createSphere(mat, objects, r * 255, g * 255, b * 255, x, y, z, radius, "arealight");
}

void RayTracer::createPlane(Material* mat, vector<RaytracingObject*> &objects, double w, double h, double rotation, double r, double g, double b, double nx, double ny, double nz, double px, double py, double pz, bool checkered, string tag) {
	objects.push_back(new Plane);
	objects[objects.size() - 1]->setPlaneNormal(nx, ny, nz);
	objects[objects.size() - 1]->setColor(r, g, b);
	objects[objects.size() - 1]->setPointOnPlane(px, py, pz);
	objects[objects.size() - 1]->setPlaneMatrix(rotation);
	objects[objects.size() - 1]->setPlaneWidthHeight(w, h);
	objects[objects.size() - 1]->setCheckered(checkered);
	objects[objects.size() - 1]->setMaterial(mat);
	objects[objects.size() - 1]->setTag(tag);
}

void RayTracer::createSphere(Material *mat, vector<RaytracingObject*> &objects, double r, double g, double b, double ox, double oy, double oz, double radius, string tag) {
	objects.push_back(new Sphere);
	objects[objects.size() - 1]->setOrigin(ox, oy, oz);
	objects[objects.size() - 1]->setColor(r, g, b);
	objects[objects.size() - 1]->setRadius(radius);
	objects[objects.size() - 1]->setMaterial(mat);
	objects[objects.size() - 1]->setTag(tag);
}

void RayTracer::createGeometricObjects() {
	cout << "Loading geometric objects..." << endl;

	Material *mat = createPhongMaterial(1, 1, 500, 100);
	createSphere(mat, objects, 100, 50, 0, -3, 4, 14, 4);

	Material *mat2 = createPhongMaterial(1, 1, 500, 100);
	createSphere(mat2, objects, 0, 20, 100, 4, 2, 8, 2);

	//Material *mat3 = createMatteMaterial(1, 1);// , 500, 100);
	//createPlane(mat3, objects, 11, 11, 0, 100, 100, 100, 0, 0, -1, 0, 10, 20, false);//back wall

	Material *mat4 = createMatteMaterial(1, 1);// , 500, 100);
	createPlane(mat4, objects, 20, 10, 0, 100, 100, 100, 0, 1, 0, 0, 0, 10, false);//floor

	//Material *mat5 = createMatteMaterial(1, 1);// , 500, 100);
	//createPlane(mat5, objects, 11, 11, 0, 100, 100, 100, 0, -1, 0, 0, 20, 10, false);//ceiling

	//Material *mat6 = createMatteMaterial(1, 1);// , 500, 100);
	//createPlane(mat6, objects, 10, 10, 0, 100, 0, 0, 1, 0, 0, -11, 10, 10, false);//left wall

	//Material *mat7 = createMatteMaterial(1, 1);// , 500, 100);
	//createPlane(mat7, objects, 10, 10, 0, 0, 100, 0, -1, 0, 0, 11, 10, 10, false);//right wall
}

void RayTracer::render() {
	srand(NULL);

	//loop through pixels and shoot rays into scene 

	//create clock variable to record miliseconds of rendering time
	clock_t begin = clock();

	cout << "Rendering image..." << endl;
	cout << "Getting initial time estimate. Please wait..." << endl;
	
	int step = bmp.height / 10;
	step = bmp.height / step;

	for (unsigned int y = 0; y < bmp.height; y++) {
		if (y % step == 0) {
			cout << int(((double)y / bmp.height) * 100) << " percent complete." << endl;
		}

		if (y % 100 == 0 && y != 0) { //display time estimate
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			if ((elapsed_secs / y) * (bmp.height - y) * 3 < 60)
				std::cout << "Image will be rendered in approximately " << (elapsed_secs / y) * (bmp.height - y) * 3<< " seconds..." << endl;
			else
				std::cout << "Image will be rendered in approximately " << (elapsed_secs / y) * (bmp.height - y) / 60 * 3 << " minutes..." << endl;
		}
		for (unsigned int x = 0; x < bmp.width; x++) {

			RGB rgb(20, 20, 20);
			sample.jittered();
			//sample.mapSamplesToDisk();
			sample.createHemisphereSamples();

			for (unsigned int i = 0; i < rectangleAreaLights.size(); i++) {
				rectangleAreaLights[i]->generateSamples();
			}

			for (unsigned int i = 0; i < pointLights.size(); i++) {
				pointLights[i]->generateSamples();
			}

			//vector<Vector> samplePoints = rectangleAreaLights[0]->getSamplePoints();

			//for (int i = 0; i < samplePoints.size(); i++) {
			//	bmp.setPixelColor(samplePoints[i].x * bmp.width, samplePoints[i].y * bmp.height, 255, 255, 255);
			//}

			//for (int j = 0; j < sample.numberOfSamples; j++) {
			//	cout << "x: " << sample.samples[j].x << endl;
			//	cout << "y: " << sample.samples[j].y << endl;
			//}

			
			//for (int i = 0; i < sample.numberOfHemisphereSamples; i++) {
			//	double y = sample.hemisphereSamples3D[i].y;
			//	if (y >= 0)
			//		bmp.setPixelColor(((sample.hemisphereSamples3D[i].x + 1) / 2) * bmp.width, ((sample.hemisphereSamples3D[i].z + 1) / 2)* bmp.height, 255, 255, 255);// , y * 255, y * 255, y * 255);
			//	else 
			//		bmp.setPixelColor(((sample.hemisphereSamples3D[i].x + 1) / 2) * bmp.width, ((sample.hemisphereSamples3D[i].z + 1) / 2)* bmp.height, 255, 0, 0);
			//}
			
			//x = y = 9999;
			//sample the image
			
			
			for (unsigned int i = 0; i < sample.numberOfSamples; i++) {
				//bmp.setPixelColor(sample.samples[i].x * bmp.width, sample.samples[i].y * bmp.width, 20, 200, 20);
				//bmp.setPixelColor(sample.diskSamples[i].x * bmp.width, sample.diskSamples[i].y * bmp.width, 20, 200, 20);
				//bmp.setPixelColor(sample.hemisphereSamples[i].x * bmp.width, sample.hemisphereSamples[i].y * bmp.width, 20, sample.hemisphereSamples[i].z * 255, 20);

				Vector rayOrigin;
				Vector primaryRay = cam.pinholeCamera(x, y, sample.samples[i].x, sample.samples[i].y, cam, bmp, rayOrigin);
				//Vector primaryRay = cam.thinlensCamera(x, y, sample.samples[i].x, sample.samples[i].y, sample.diskSamples[i].x, sample.diskSamples[i].y, cam, bmp, rayOrigin);

				//find closest object
				RaytracingObject *object = NULL;
				double minDepth = DBL_MAX;
				double depth = DBL_MAX;

				//material used for shading object that ray intersects
				Material *material = NULL;

				//shade used to collect data for shading such as intersection points
				Shade shade;

				for (unsigned int i = 0; i < objects.size(); i++) {
					objects[i]->intersectRay(depth, primaryRay, rayOrigin);
					if (depth < minDepth) {
						object = objects[i];
						minDepth = depth;
						shade.intersectionPoint = rayOrigin + (primaryRay * depth);
					}
				}

				if (object != NULL) {
					material = object->getMaterial();
					shade.normal = object->getNormal();
					shade.wo = primaryRay * -1;
					shade.colorOfObject = object->getColor();
					shade.sample = &sample;
					if (object->getTag() == "arealight") { //if ray hits the area light, then just return a white color for the light its-self
						rgb += object->getColor();
					}
					else {
						rgb += shade.performShading(object->getMaterial()->getAmbientBRDF(), object->getMaterial()->getDiffuseBRDF(), object->getMaterial()->getSpecularBRDF(), objects, ambientLight, pointLights, rectangleAreaLights);
					}
				}
			}

			rgb /= sample.numberOfSamples;
			
			//clamp rgb (very crude)
			double maxNum = max(max(rgb.r, rgb.g), rgb.b);
			if (maxNum > 255) {
				rgb /= maxNum;
				rgb.r *= 255;
				rgb.g *= 255;
				rgb.b *= 255;
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