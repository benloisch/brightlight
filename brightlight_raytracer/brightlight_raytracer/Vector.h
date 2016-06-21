#pragma once //serves same purpose as include guards
//pragma once has advantages such as avoiding name clashes

#include "matrix.h"
#include <math.h>

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

		inline Vector& Vector::operator=(const Vector &rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->w = rhs.w;

			return *this;
		}
		inline //return this + rhs
		Vector Vector::operator+(const Vector &rhs) const {
			Vector out(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
			return out;
		}
		inline //return this - rhs
		Vector Vector::operator-(const Vector &rhs) const {
			Vector out(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
			return out;
		}
		inline //return element-wise multiplication with scalar rhs
		Vector Vector::operator*(const double rhs) const {
			Vector out(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs);
			return out;
		}
		inline //return element-wise division with scalar rhs
		Vector Vector::operator/(const double rhs) const {
			Vector out(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs);
			return out;
		}
		inline //return dot product of this (dot) rhs
		double Vector::operator*(const Vector &rhs) const {
			return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z + this->w * rhs.w);
		}
		inline //return cross product of this (cross) rhs
		Vector Vector::operator^(const Vector &rhs) const {
			Vector out;
			out.x = (this->y * rhs.z) - (this->z * rhs.y);
			out.y = (this->z * rhs.x) - (this->x * rhs.z);
			out.z = (this->x * rhs.y) - (this->y * rhs.x);
			out.w = rhs.w;

			return out;
		}
		inline //return this * rhs (vector * matrix) ROW MAJOR
		Vector Vector::operator*(const Matrix &inMat)
		{
			Vector result;
			//[x, y, z, w]   *   [00, 01, 02, 03]
			//                   [10, 11, 12, 13]
			//                   [20, 21, 22, 23]
			//                   [30, 31, 32, 33]

			result.x = (this->x * inMat.m[0][0]) + (this->y * inMat.m[1][0]) + (this->z * inMat.m[2][0]) + (this->w * inMat.m[3][0]);
			result.y = (this->x * inMat.m[0][1]) + (this->y * inMat.m[1][1]) + (this->z * inMat.m[2][1]) + (this->w * inMat.m[3][1]);
			result.z = (this->x * inMat.m[0][2]) + (this->y * inMat.m[1][2]) + (this->z * inMat.m[2][2]) + (this->w * inMat.m[3][2]);
			result.w = (this->x * inMat.m[0][3]) + (this->y * inMat.m[1][3]) + (this->z * inMat.m[2][3]) + (this->w * inMat.m[3][3]);

			return result;
		}
		inline
		void Vector::normalize()
		{
			double tempx = x / sqrt((x * x) + (y * y) + (z * z) + (w * w));
			double tempy = y / sqrt((x * x) + (y * y) + (z * z) + (w * w));
			double tempz = z / sqrt((x * x) + (y * y) + (z * z) + (w * w));
			double tempw = w / sqrt((x * x) + (y * y) + (z * z) + (w * w));

			x = tempx;
			y = tempy;
			z = tempz;
			w = tempw;
		}
		inline
		double Vector::getMagnitude()
		{
			return sqrt((x * x) + (y * y) + (z * z) + (w * w));
		}

	};
}