#include "Sample.h"

Sample::Sample() {
	samples = NULL;
	numberOfSamples = 0;
}

void Sample::setNumberOfSamples(unsigned int size) {
	numberOfSamples = size;
	try {
		samples = new Point_2D[size];
	}
	catch (...) {
		throw exception("Error in Sample.setNumberOfSamples()");
	}
}

Sample::~Sample() {
	delete[] samples;
}