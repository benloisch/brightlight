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

	inline 
	void ImageBMP::setPixelColor(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
		red[x][y] = r;
		green[x][y] = g;
		blue[x][y] = b;
	}
	inline 
	RGB ImageBMP::getPixelColor(unsigned int x, unsigned int y) {
		RGB rgb;

		try {
			rgb.r = red[x][y];
			rgb.g = green[x][y];
			rgb.b = blue[x][y];
		}
		catch (...) {
			throw exception("Error in ImageBMP.getPixelColor()");
			cleanup();
		}

		return rgb;
	}
	
	void setInitialBMPColor(unsigned char r, unsigned char g, unsigned char b);

};