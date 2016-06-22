#include "Sample.h"

Sample::Sample() {
	samples = NULL;
	numberOfSamples = 0;
	e = 2.718281828459;
}

void Sample::setE(double e) {
	this->e = e;
}

void Sample::setNumberOfSamples(unsigned int size) {
	numberOfSamples = size;
	try {
		samples = new Point_2D[size];
		diskSamples = new Point_2D[size];
	}
	catch (...) {
		throw exception("Error in Sample.setNumberOfSamples()");
	}
}

void Sample::initializeHemisphereSamples() {
	try {
		hemisphereSamples = new Vector[numberOfSamples];
	}
	catch (...) {
		cleanup();
		throw exception("Error in Sample.setNumberOfSamples()");
	}
}

void Sample::cleanup() {
	delete[] samples;
	delete[] diskSamples;
	delete[] hemisphereSamples;
}

Sample::~Sample() {
	delete[] samples;
	delete[] hemisphereSamples;
}