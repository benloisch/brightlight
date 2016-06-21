#pragma once

class RGB {
public:
	double r;
	double g;
	double b;

	RGB();
	RGB(double r, double g, double b);
	inline 
	RGB& RGB::operator+=(RGB &rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}

	inline 
	RGB& RGB::operator/=(double rhs) {
		r = r / rhs;
		g = g / rhs;
		b = b / rhs;
		return *this;
	}
};