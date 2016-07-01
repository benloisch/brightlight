#pragma once

class RGB {
public:
	double r;
	double g;
	double b;

	RGB();
	RGB(double r, double g, double b);
	inline RGB RGB::operator*(RGB &rhs) {
		RGB rgb;
		rgb.r = this->r * rhs.r;
		rgb.g = this->g * rhs.g;
		rgb.b = this->b * rhs.b;
		return rgb;
	}

	inline RGB RGB::operator+(RGB &rhs) {
		RGB rgb;
		rgb.r = this->r + rhs.r;
		rgb.g = this->g + rhs.g;
		rgb.b = this->b + rhs.b;
		return rgb;
	}

	inline RGB RGB::operator*(double rhs) {
		RGB rgb;
		rgb.r = r * rhs;
		rgb.g = g * rhs;
		rgb.b = b * rhs;
		return rgb;
	}

	inline RGB& RGB::operator=(const RGB &rhs) {
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		return *this;
	}

	inline RGB& RGB::operator+=(const RGB &rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}

	inline RGB& RGB::operator/=(const double rhs) {
		r = r / rhs;
		g = g / rhs;
		b = b / rhs;
		return *this;
	}
};