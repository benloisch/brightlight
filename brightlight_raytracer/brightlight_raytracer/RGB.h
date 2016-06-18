#pragma once

class RGB {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;

	RGB();
	RGB(unsigned char r, unsigned char g, unsigned char b);
	RGB& operator+=(RGB &rhs);
	RGB& operator/=(double rhs);
};