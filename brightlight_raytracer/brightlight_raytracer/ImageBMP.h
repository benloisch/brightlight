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
	~ImageBMP();

	void cleanup();
	void createBMP(unsigned int width, unsigned int height, string fileName);
	void saveBMP();
	void setPixelColor(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
	RGB getPixelColor(unsigned int x, unsigned int y);
	void setInitialBMPColor(unsigned char r, unsigned char g, unsigned char b);

};