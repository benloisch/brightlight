#pragma once

#include <vector>
#include <math.h>
#include <random>
#include <time.h>
#include "Point_2D.h"

using namespace std;

class Sample {
public:

	inline 
	static vector<Point_2D> multiJittered() {

		

	}

	inline 
	static vector<Point_2D> jittered(int samples) {

		vector<Point_2D> points;
		double n = sqrt(samples);
		for (double x = 0; x < n; x++) {
			for (double y = 0; y < n; y++) {
				srand(unsigned int(time(0)));
				double xVal = (x / n) + (((double)rand() / (RAND_MAX)) / n);
				double yVal = (y / n) + (((double)rand() / (RAND_MAX)) / n);
				points.push_back(Point_2D(xVal, yVal));
			}
		}

		return points;
	}

};