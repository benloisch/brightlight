#include "Sample.h"

Sample::Sample() {
	samples = NULL;
	diskSamples = NULL;
	hemisphereSamples2D = NULL;
	hemisphereSamples3D = NULL;
	numberOfSamples = 4;
	numberOfHemisphereSamples = 4;
	e = 2.718281828459;
	roomDepth = 100;
	ambientAmountToShade = 0;
}

void Sample::setRoomDepth(double room) {
	roomDepth = room;
}

void Sample::setAmbientAmountToShade(double a) {
	ambientAmountToShade = a;
}

void Sample::setE(double e) {
	this->e = e;
}

void Sample::setNumberOfHemisphereSamples(unsigned int size) {
	numberOfHemisphereSamples = size;
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
		hemisphereSamples2D = new Point_2D[numberOfHemisphereSamples];
		hemisphereSamples3D = new Vector[numberOfHemisphereSamples];
	}
	catch (...) {
		cleanup();
		throw exception("Error in Sample.setNumberOfSamples()");
	}
}

void Sample::cleanup() {
	delete[] samples;
	delete[] diskSamples;
	delete[] hemisphereSamples2D;
	delete[] hemisphereSamples3D;
}

Sample::~Sample() {
	delete[] samples;
	delete[] diskSamples;
	delete[]hemisphereSamples2D;
	delete[] hemisphereSamples3D;
}