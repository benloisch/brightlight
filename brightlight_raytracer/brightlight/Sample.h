#pragma once

#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include "Point_2D.h"
#include "Vector.h"

using namespace std;
using namespace blvector;

const double PI = 3.14159265359;

class Sample {
public:

	double e;
	Point_2D *samples;
	Point_2D *diskSamples;
	Point_2D *hemisphereSamples2D;
	Vector *hemisphereSamples3D;
	unsigned int numberOfSamples;
	unsigned int numberOfHemisphereSamples;
	double ambientAmountToShade;
	double roomDepth;

	Sample();
	~Sample();

	void setRoomDepth(double room);
	void setAmbientAmountToShade(double a);
	void setE(double e);
	void cleanup();
	void setNumberOfSamples(unsigned int size);
	void setNumberOfHemisphereSamples(unsigned int size);
	void initializeHemisphereSamples();

	inline void createHemisphereSamples() {

		int a = 0;
		int n = (int)sqrt(numberOfHemisphereSamples);
		for (double y = 0; y < n; y++) {
			for (double x = 0; x < n; x++) {
				double xVal = (x / n) + (((double)rand() / (double)(RAND_MAX)) / n);
				double yVal = (y / n) + (((double)rand() / (double)(RAND_MAX)) / n);
				hemisphereSamples2D[a].x = xVal;
				hemisphereSamples2D[a].y = yVal;
				a++;
			}
		}

		for (unsigned int i = 0; i < numberOfHemisphereSamples; i++) {
			double cos_phi = cos(2.0 * PI * hemisphereSamples2D[i].x);
			double sin_phi = sin(2.0 * PI * hemisphereSamples2D[i].x);
			double cos_theta = pow((1.0 - hemisphereSamples2D[i].y), 1.0 / (e + 1.0));
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
			double z = sin_theta * cos_phi;
			double x = sin_theta * sin_phi;
			double y = cos_theta;

			hemisphereSamples3D[i].x = x;
			hemisphereSamples3D[i].y = y;
			hemisphereSamples3D[i].z = z;
		}
	}

	//elliptical grid mapping from unit square to unit circle
	inline void mapSamplesToDisk() {
		for (unsigned int i = 0; i < numberOfSamples; i++) {

			double x = samples[i].x;
			double y = samples[i].y;

			//convert from [0,1] to [-1, 1] for x and y
			x = (2 * x) - 1;
			y = (2 * y) - 1;

			diskSamples[i].x = x * sqrt(1 - (y*y) / 2);
			diskSamples[i].y = y * sqrt(1 - (x*x) / 2);

			//diskSamples[i].x = (diskSamples[i].x + 1) / 2;
			//diskSamples[i].y = (diskSamples[i].y + 1) / 2;
		}
	}

	inline Point_2D* jittered() {
		int i = 0;
		int n = (int)sqrt(numberOfSamples);
		for (double y = 0; y < n; y++) {
			for (double x = 0; x < n; x++) {
				double xVal = (x / n) + (((double)rand() / (double)(RAND_MAX)) / n);
				double yVal = (y / n) + (((double)rand() / (double)(RAND_MAX)) / n);
				samples[i].x = xVal;
				samples[i].y = yVal;
				i++;
			}
		}

		return samples;
	}

};