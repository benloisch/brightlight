#pragma once

#include "RGB.h"

class Sample {
public:

	void static regularSampling(int px, int py, int sampleSize, double fov, double aspectRatio, RGB &rgb);

};