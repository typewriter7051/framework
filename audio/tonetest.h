#include "Sound.h"

class ToneTest : public sound::Synth {

	ToneTest() {

		samples.resize(2048);

	}

	ToneTest(unsigned int numSamples) {

		samples.resize(numSamples);

	}

	std::vector<float>* generateBuffer(unsigned int numSamples) override {

		for (int i = 0; i < numSamples; i++) {

		}

	}

};