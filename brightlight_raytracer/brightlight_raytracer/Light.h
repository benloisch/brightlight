#pragma once

#include "Vector.h"
#include "RGB.h"

using namespace blvector;

class Light
{
public:

	virtual Vector getLightDirection() = 0;
	virtual Vector getLightOrigin() = 0;
	virtual RGB getLightRadiance() = 0;

};