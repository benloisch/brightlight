#pragma once
#include <iostream>
#include <string>

#include "Vector.h"
using namespace blvector;
using namespace std;

//This file has useful functions and defines

//Floating-point division requires more cycles than multiplication.
//Thus, if dividing by PI, instead, multiply by the inverse of PI.
const double inversePI = 0.3183098861837906;
//const double PI = 3.14159265359;
//const double e = 2.718281828459;

void printVector(Vector v) {
	cout << "V: " << to_string(v.x) << ", " << to_string(v.y) << ", " << to_string(v.z) << ", " << to_string(v.w) << endl;
}

void printMatrix(Matrix m) {
	cout << to_string(m.m[0][0]) << ", " << to_string(m.m[0][1]) << ", " << to_string(m.m[0][2]) << ", " << to_string(m.m[0][3]) << endl;
	cout << to_string(m.m[1][0]) << ", " << to_string(m.m[1][1]) << ", " << to_string(m.m[1][2]) << ", " << to_string(m.m[1][3]) << endl;
	cout << to_string(m.m[2][0]) << ", " << to_string(m.m[2][1]) << ", " << to_string(m.m[2][2]) << ", " << to_string(m.m[2][3]) << endl;
	cout << to_string(m.m[3][0]) << ", " << to_string(m.m[3][1]) << ", " << to_string(m.m[3][2]) << ", " << to_string(m.m[3][3]) << endl;
}