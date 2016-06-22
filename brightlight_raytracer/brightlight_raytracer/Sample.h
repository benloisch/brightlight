#pragma once

#include <vector>
#include <math.h>
#include <random>
#include <time.h>
#include "Point_2D.h"
#include "Vector.h"
//#include "Utilities.h"

using namespace std;
using namespace blvector;

const double PI = 3.14159265359;

class Sample {
public:

	double e;
	Point_2D *samples;
	Point_2D *diskSamples;
	Vector *hemisphereSamples;
	unsigned int numberOfSamples;

	Sample();
	~Sample();


	void setE(double e);
	void cleanup();
	void setNumberOfSamples(unsigned int size);
	void initializeHemisphereSamples();

	inline void mapDiskToHemisphere() {

		for (unsigned int i = 0; i < numberOfSamples; i++) {
			double cos_phi = cos(2.0 * PI * samples[i].x);
			double sin_phi = sin(2.0 * PI * samples[i].x);
			double cos_theta = pow((1.0 - samples[i].y), 1.0 / (e + 1.0));
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
			double x = sin_theta * cos_phi;
			double y = sin_theta * sin_phi;
			double z = cos_theta;

			hemisphereSamples[i].x = x;
			hemisphereSamples[i].y = y;
			hemisphereSamples[i].z = z;
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

			diskSamples[i].x = (diskSamples[i].x + 1) / 2;
			diskSamples[i].y = (diskSamples[i].y + 1) / 2;
		}
	}

	inline Point_2D* jittered() {
		srand(unsigned int(time(0)));
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