#include "ImageBMP.h"

#include <iostream>

ImageBMP::ImageBMP(unsigned int width, unsigned int height, string fileName) {
	this->width = width;
	this->height = height;
	this->fileName = fileName;

	red = NULL;
	green = NULL;
	blue = NULL;

	try {
	
		//try to intialize pointers to a pointer array of width * height

		red = new unsigned char*[width];
		for (unsigned int i = 0; i < width; i++) {
			red[i] = new unsigned char[height];
			for (unsigned int j = 0; j < height; j++) {
				red[i][j] = 0;
			}
		}

		green = new unsigned char*[width];
		for (unsigned int i = 0; i < width; i++) {
			green[i] = new unsigned char[height];
			for (unsigned int j = 0; j < height; j++) {
				green[i][j] = 0;
			}
		}

		blue = new unsigned char*[width];
		for (unsigned int i = 0; i < width; i++) {
			blue[i] = new unsigned char[height];
			for (unsigned int j = 0; j < height; j++) {
				blue[i][j] = 0;
			}
		}

		if (red == NULL || green == NULL || blue == NULL) {
			throw exception("Could not intialize character pointer.");
		}
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
}

ImageBMP::~ImageBMP() {

	for (unsigned int i = 0; i < width; i++) {
		delete red[i];
		delete green[i];
		delete blue[i];
	}

	delete red;
	delete green;
	delete blue;

	red = NULL;
	green = NULL;
	blue = NULL;
}

bool ImageBMP::saveBMP() {
	ofstream file;

	try {
		cout << "writing BMP file..." << endl;

		WORD bfType = 'BM';

		//check for endianness of the computer and store 'BM' accordingly 
		int n = 1;
		if (*(char *)&n == 1)
			bfType = 'MB';

		//each row must be a multiple of 4 bytes
		int pad = 0;
		if ((width * 3) % 4 != 0) {
			pad = 4 - ((width * 3) % 4); //remaining bytes to be added
		}

		BITMAPFILEHEADER fh;
		fh.bfType = bfType;
		fh.bfSize = ((width * 3) + pad) * height + 54;
		fh.bfReserved1 = 0;
		fh.bfReserved2 = 0;
		fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		BITMAPINFOHEADER ih;
		ih.biSize = 40;
		ih.biWidth = width;
		ih.biHeight = height;
		ih.biPlanes = 1;
		ih.biBitCount = 24;
		ih.biCompression = 0;
		ih.biSizeImage = ((width * 3) + pad) * height;
		ih.biXPelsPerMeter = 0;
		ih.biYPelsPerMeter = 0;
		ih.biClrUsed = 0;
		ih.biClrImportant = 0;

		BITMAPFILEHEADER *pfh = &fh;
		BITMAPINFOHEADER *pih = &ih;
		
		file.open(fileName.append(".bmp"), ios::binary);//Do not you ios:out *error*
		
		if (file.is_open()) {

			file.write((char*)pfh, sizeof(fh));
			file.write((char*)pih, sizeof(ih));


			//write data of double pointer characters arrays (red, green, and blue) to bmp file
			for (int j = height - 1; j >= 0; j--) {
				for (unsigned int i = 0; i < width; i++) {
					file << blue[i][j];
					file << green[i][j];
					file << red[i][j];
				}

				//add padding bytes
				for (int i = 0; i < pad; i++) {
					file << (char)0;
				}

			}

			file.close();

			cout << "File saved." << endl;
		}
		else {
			cout << "Could not open file for writing" << endl;
		}
	}
	catch (...) {
		file.close();
		return false;
	}

	return true;
}

void ImageBMP::setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
	if (x >= width) {
		cout << "x in setPixel() cannot be greater than width of image" << endl;
		return;
	}
	
	if (y >= height) {
		cout << "y in setPixel() cannot be greater than height of image" << endl;
		return;
	}

	red[x][y] = r;
	green[x][y] = g;
	blue[x][y] = b;
}

void ImageBMP::setInitialBMPColor(unsigned char r, unsigned char g, unsigned char b) {
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++)
			this->setPixel(j, i, r, g, b);
	}
}

RGB ImageBMP::getPixel(unsigned int x, unsigned int y) {
	RGB rgb;
	rgb.r = red[x][y];
	rgb.g = green[x][y];
	rgb.b = blue[x][y];
	return rgb;
}