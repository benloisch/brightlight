#pragma once

#include <vector>
#include <math.h>
#include <random>
#include <time.h>
#include "Point_2D.h"

using namespace std;

class Sample {
public:

	Point_2D *samples;
	unsigned int numberOfSamples;

	Sample();
	~Sample();

	void setNumberOfSamples(unsigned int size);

	//elliptical grid mapping from unit square to unit circle
	inline void mapSamplesToDisk() {
		for (unsigned int i = 0; i < numberOfSamples; i++) {

			double x = samples[i].x;
			double y = samples[i].y;

			//convert from [0,1] to [-1, 1] for x and y
			x = (2 * x) - 1;
			y = (2 * y) - 1;

			samples[i].x = x * sqrt(1 - (y*y) / 2);
			samples[i].y = y * sqrt(1 - (x*x) / 2);

			samples[i].x = (samples[i].x + 1) / 2;
			samples[i].y = (samples[i].y + 1) / 2;
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