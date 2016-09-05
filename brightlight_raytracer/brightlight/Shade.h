#pragma once

#include "RaytracingObject.h"
#include "Vector.h"
#include "RGB.h"
#include "Sample.h"
#include "BRDF.h"
#include "Light.h"
#include <vector>

using namespace std;
using namespace blvector;

#define dotproductmax(a, b) ((a > b) ? a : b)
const double epsilon = 0.00001;

class Shade
{
public: 

	Sample *sample;
	Vector wi;
	Vector wo;
	Vector intersectionPoint;
	Vector normal;
	RGB colorOfObject;

	BRDF *ambientBRDF;
	BRDF *diffuseBRDF;
	BRDF *specularBRDF;

	Shade();

	inline bool testShadowRay(vector<RaytracingObject*> &objects, Vector &shadowRay, Vector &shadowRayOrigin, double depthToPointLight) {
		double depth = DBL_MAX;

		for (unsigned int n = 0; n < objects.size(); n++) {
			objects[n]->intersectRay(depth, shadowRay, shadowRayOrigin);
			if (depth < depthToPointLight && abs(depth) > epsilon && objects[n]->getTag() != "arealight") {
				return true;
			}
		}
		return false;
	}
	
	inline bool testShadowRayAmbientOcclusion(vector<RaytracingObject*> &objects, Vector &shadowRay, Vector &shadowRayOrigin, double extendRoomDepth) {
		double depth = DBL_MAX;

		for (unsigned int n = 0; n < objects.size(); n++) {
			objects[n]->intersectRay(depth, shadowRay, shadowRayOrigin);
			if (depth < extendRoomDepth && abs(depth) > epsilon && objects[n]->getTag() != "arealight") {
				return true;
			}
		}

		return false;
	}

	inline RGB calculateAmbientOcclusion(vector<RaytracingObject*> &objects, vector<Light*> &ambient) {
		RGB rgbAmbient;
		//calculate ambient light
		for (unsigned int i = 0; i < ambient.size(); i++) {
			//setup orthonormal base to project rays off of
			Vector up = normal;
			Vector right;
			Vector forward;
			if (up.x == 0 && up.y == 1 && up.z == 0) {
				right.x = 1;
				forward.z = 1;
			}
			else if (up.x == 0 && up.y == -1 && up.z == 0) {
				right.x = 1;
				forward.z = 1;
			}
			else {
				right = Vector(0, 1, 0, 0) ^ up;
				forward = up ^ right;
			}

			Matrix m;
			m.setRow1(right.x, right.y, right.z, 0);
			m.setRow2(up.x, up.y, up.z, 0);
			m.setRow3(forward.x, forward.y, forward.z, 0);

			for (unsigned int a = 0; a < sample->numberOfHemisphereSamples; a++){
				//calculate ray to shoot out based off of hemisphere sample points
				Vector hempisphereRay = Vector(sample->hemisphereSamples3D[a].x, sample->hemisphereSamples3D[a].y, sample->hemisphereSamples3D[a].z, 0);
				Vector ray = hempisphereRay * m;
				ray.normalize();
				if (!testShadowRayAmbientOcclusion(objects, ray, intersectionPoint, sample->roomDepth)) {
					if (ambientBRDF != NULL)
						rgbAmbient += colorOfObject * ambientBRDF->calculateBRDF() * ambient[i]->getLightRadiance();
				}
				else {
					if (ambientBRDF != NULL)
						rgbAmbient += colorOfObject * ambientBRDF->calculateBRDF() * ambient[i]->getLightRadiance() * sample->ambientAmountToShade;
				}
			}

			rgbAmbient /= sample->numberOfHemisphereSamples;
		}

		return rgbAmbient;
	}

	inline RGB calculateRectangleAreaLight(vector<RaytracingObject*> &objects, vector<Light*> &areaLight) {
		RGB areaTotal;
		//calculate area light
		for (unsigned int i = 0; i < areaLight.size(); i++) {

			vector<Vector> samplePoints = areaLight[i]->getSamplePoints();
			RGB rgbArea;

			for (int a = 0; a < areaLight[i]->getNumberOfSamplePoints(); a++){
				//calculate ray to shoot out based off of area sample points
				Vector ray = samplePoints[a] - intersectionPoint;
				double depth = ray.getMagnitude();
				ray.normalize();
				wi = ray;

				if (!testShadowRay(objects, wi, intersectionPoint, depth)) {
					if ((wi * -1) * areaLight[i]->getLightDirection() > 0) {
						if (diffuseBRDF != NULL)
							rgbArea += colorOfObject * diffuseBRDF->calculateBRDF() * areaLight[i]->getLightRadiance() * dotproductmax((wi * normal), 0);
						if (specularBRDF != NULL)
							rgbArea += areaLight[i]->getLightRadiance() * specularBRDF->calculateBRDF(wi, normal, wo) * dotproductmax((wi * normal), 0);
					}
				}
			}

			rgbArea /= areaLight[i]->getNumberOfSamplePoints();
			areaTotal += rgbArea;
		}

		return areaTotal;
	}

	inline RGB calculateAreaPointLight(vector<RaytracingObject*> &objects, vector<Light*> &areaLight) {
		RGB areaTotal;
		//calculate area light
		for (unsigned int i = 0; i < areaLight.size(); i++) {

			RGB rgbArea;

			vector<Vector> samplePoints = areaLight[i]->getSamplePoints();
			//scale points (range -1 to 1) to match radius of sphere
			for (unsigned int b = 0; b < samplePoints.size(); b++) {
				samplePoints[b] = samplePoints[b] * areaLight[i]->getRadius();
				samplePoints[b] = samplePoints[b] + Vector(areaLight[i]->getLightOrigin().x, areaLight[i]->getLightOrigin().y, areaLight[i]->getLightOrigin().z, 0);
			}

			for (int a = 0; a < areaLight[i]->getNumberOfSamplePoints(); a++) {
				//calculate ray to shoot out based off of area sample points
				Vector ray = samplePoints[a] - intersectionPoint;
				double depth = ray.getMagnitude();
				ray.normalize();
				wi = ray;

				if (!testShadowRay(objects, wi, intersectionPoint, depth)) {
					if (diffuseBRDF != NULL)
						rgbArea += colorOfObject * diffuseBRDF->calculateBRDF() * areaLight[i]->getLightRadiance() * dotproductmax((wi * normal), 0);
					if (specularBRDF != NULL)
						rgbArea += areaLight[i]->getLightRadiance() * specularBRDF->calculateBRDF(wi, normal, wo) * dotproductmax((wi * normal), 0);
				}
			}

			rgbArea /= areaLight[i]->getNumberOfSamplePoints();
			areaTotal += rgbArea;
		}

		return areaTotal;
	}

	inline RGB performShading(BRDF *ambientBRDF, BRDF* diffuseBRDF, BRDF* specularBRDF, vector<RaytracingObject*> &objects, vector<Light*> &ambient, vector<Light*> &areaPointLight, vector<Light*> &rectangleAreaLight) {

		this->ambientBRDF = ambientBRDF;
		this->diffuseBRDF = diffuseBRDF;
		this->specularBRDF = specularBRDF;

		RGB rgbAmbient;
		rgbAmbient = calculateAmbientOcclusion(objects, ambient);

		//calculate rectangle area lights
		RGB rgbRectangleArea;
		rgbRectangleArea = calculateRectangleAreaLight(objects, rectangleAreaLight);

		//calculate area point lights
		RGB rgbPointArea;
		rgbPointArea = calculateAreaPointLight(objects, areaPointLight);

		return rgbAmbient + rgbPointArea + rgbRectangleArea;
	}

};