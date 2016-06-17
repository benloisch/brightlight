#pragma once //serves same purpose as include guards
//pragma once has advantages such as avoiding name clashes

#include "matrix.h"

using namespace blmatrix;

namespace blvector {
	class Vector
	{
	public:

		double x;
		double y;
		double z;
		double w;

		Vector();
		Vector(double x, double y, double z, double w);
		Vector& operator=(const Vector& rhs);
		Vector operator+(const Vector& rhs)const;//return this + rhs
		Vector operator-(const Vector& rhs)const;//return this - rhs
		Vector operator*(const double rhs)const;//return element-wise multiplication with scalar rhs
		Vector operator/(const double rhs)const;//return element-wise division with scalar rhs
		double operator*(const Vector& rhs)const;//return dot product of this (dot) rhs
		Vector operator^(const Vector& rhs)const;//return cross product of this (cross) rhs
		Vector operator*(const Matrix& rhs);//return this * rhs (vector * matrix) ROW MAJOR

		void normalize();
		double getMagnitude();
	};
}