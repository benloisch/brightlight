#include "RGB.h"

RGB::RGB() {
	r = 0;
	g = 0;
	b = 0;
}

RGB::RGB(unsigned char r, unsigned char g, unsigned char b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

RGB& RGB::operator+=(RGB &rhs) {
	this->r += rhs.r;
	this->g += rhs.g;
	this->b += rhs.b;
	return *this;
}

RGB& RGB::operator/=(double rhs) {
	this->r /= rhs;
	this->g /= rhs;
	this->b /= rhs;
	return *this;
}