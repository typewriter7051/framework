#include "utility.h"

void Utility::setGain(float g) {

	gain = g;

}

void Utility::setMix(float m) {

	if (m > 1) mix = 1;
	else if (m < 0) mix = 0;
	else mix = m;

}

void Utility::setWidth(float w) {

	if (w > 1) width = 1;
	else if (w < 0) width = 0;
	else width = w;

}

void Utility::setPan(float p) {

	if (p > 1) pan = 1;
	else if (p < -1) pan = -1;
	else pan = p;

}

void Utility::processBuffer(std::vector<float>& buffer) {

	// Gain and mix automatically applied after this function.

	for (int f = 0; f < buffer.size(); f++) {

		// Apply width.
		midPoint = buffer.at(f) * 0.5 + buffer.at(f + 1) * 0.5;

		buffer.at(f) += (midPoint - buffer.at(f)) * (1 - width);
		buffer.at(f + 1) += (midPoint - buffer.at(f + 1)) * (1 - width);

		// Apply pan.
		if (pan < 0) buffer.at(f + 1) *= 1 + pan;
		if (pan > 0) buffer.at(f) *= 1 - pan;

	}

}