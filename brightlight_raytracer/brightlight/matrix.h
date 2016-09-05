#pragma once

namespace blmatrix {

	class Matrix
	{
	public:

		double m[4][4];

		Matrix();
		Matrix(const Matrix &inMat);

		double det3x3(double, double, double, double, double, double, double, double, double);

		void setRow1(double, double, double, double);
		void setRow2(double, double, double, double);
		void setRow3(double, double, double, double);
		void setRow4(double, double, double, double);

		void setXrot(double);//in degrees
		void setYrot(double);
		void setZrot(double);

		void setScale(double, double, double);
		void setTranslate(double, double, double);
		void setRotArb(double, double, double, double);

		void setTranspose();
		Matrix tranpose();
		void setInverse();
		Matrix inverse();
		void setIdentity();
		void zeroOutElements();

		Matrix &operator=(const Matrix inMat);
		Matrix operator*(const Matrix inMat);
		Matrix operator*(const double inScalar);
		Matrix operator+(const Matrix inMat);
		Matrix operator-(const Matrix inMat);

	};

}