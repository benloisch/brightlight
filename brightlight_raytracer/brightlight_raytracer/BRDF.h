#pragma once

#include "Shade.h"
#include "RGB.h"
#include "Vector.h"

using namespace blvector;

class BRDF
{
public:

	virtual RGB perfectDiffuseReflectance() = 0;
	virtual RGB bihemisphericalReflectance() = 0;

};