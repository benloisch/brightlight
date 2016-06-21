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

	inline 
	Point_2D* jittered() {

		int i = 0;
		double n = sqrt(numberOfSamples);
		for (double y = 0; y < n; y++) {
			for (double x = 0; x < n; x++) {
				srand(unsigned int(time(0)));
				double xVal = (x / n) + (((double)rand() / (RAND_MAX)) / n);
				double yVal = (y / n) + (((double)rand() / (RAND_MAX)) / n);
				samples[i].x = xVal;
				samples[i].y = yVal;
				i++;
			}
		}

		return samples;
	}

};