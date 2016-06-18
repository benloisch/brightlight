#pragma once

#include "RGB.h"
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

class ImageBMP {
private:

	string fileName;
	unsigned char **red;
	unsigned char **green;
	unsigned char **blue;

public:

	unsigned int width;
	unsigned int height;

	ImageBMP();
	ImageBMP(unsigned int width, unsigned int height, string fileName);
	~ImageBMP();

	bool saveBMP();
	void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
	RGB getPixel(unsigned int x, unsigned int y);
	void setInitialBMPColor(unsigned char r, unsigned char g, unsigned char b);

};