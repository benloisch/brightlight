#pragma once

#include "RGB.h"

class Material
{
public:
	virtual RGB shade() = 0;

};