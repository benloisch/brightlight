#pragma once

#include "Vector.h"
#include "RGB.h"
#include "Point_2D.h"
#include <vector>

using namespace std;

using namespace blvector;

//const double PI = 3.14159265359;

class Light
{
public:

	virtual void setRadianceScalingFactor(double i) = 0;
	virtual void setLightColor(double r, double g, double b) = 0;
	virtual double getRadianceScalingFactor() = 0;
	virtual RGB getLightColor() = 0; 
	virtual RGB getLightRadiance() = 0; 
	virtual Vector getLightDirection() { return Vector(0, 0, 0, 0); }; //used for directional and point lights
	virtual double getRadius() { return 0; }; //used for point lights
	virtual Vector getLightOrigin() { return Vector(0, 0, 0, 0); }; //used for point lights
	virtual void setLightOrigin(double x, double y, double z) {}; //used for point lights and area lights
	virtual void setLightDirection(double x, double y, double z) {}; //used for directional lights and area lights

	virtual void setRectangleAreaLightWidthHeight(double x, double y) {}; //used for area lights
	virtual void setRectangleAreaLightMatrix(double radianRotation) {}; //used for area lights
	virtual void setRectangleAreaLightSamplePointAmount(int samplePointAmount) {}; //used for area lights
	virtual int getNumberOfSamplePoints() { return 0; }; //used for area lights
	virtual void generateSamples() {}; // used for area lights
	virtual vector<Vector> getSamplePoints() { vector<Vector> none; return none; }; //used for area lights
	virtual void setAreaPointLightSamplePointAmount(int samplePointAmount) {}; // used for area lights
	virtual void setPointLightRadius(double radius) {}; //used for area lights
};