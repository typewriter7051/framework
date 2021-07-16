#include "sound.h"

std::vector<float>* sound::Synth::getBuffer(unsigned int numSamples) {

	// detect change in sample rate.
	if (samples.size() != numSamples) samples.resize(numSamples);

	return channel->processBuffer(generateBuffer());

}

void sound::Effect::processAndHandleBuffer(std::vector<float>& b) {

	samples.assign(b);

	processBuffer(samples);

	for (int s = 0; s < samples.size(); s++) {

		// Mix processing.
		// wet = mix * wet + (1 - mix) * dry.
		samples.at(s) = mix * samples.at(s) + (1 - mix) * b.at(s);

		// Gain processing.
		samples.at(s) *= gain;

	}


}

std::vector<float>* sound::Channel::processBuffer(std::vector<float>& buffer) {

	// copy the values of buffer into samples.
	samples.assign(buffer);

	for (auto& e : effects) {

		e.processBuffer(samples);

	}

	return &samples;

}

/*bool sound::SoundHandler::onGetData(Chunk& data) override {

	// Add every output to the master buffer.

	std::vector<float>* channelBuffer;

	std::vector<float> masterBuffer; // float cast of "samples" vector.
	masterBuffer.resize(bufferSize);
	std::fill(masterBuffer.begin(), masterBuffer.end(), 0);

	for (int g = 0; g < synths.size(); g++) {

		channelBuffer = synths.at(g)->getBuffer();

		// Add the channel output to the master buffer.
		for (int s = 0; s < bufferSize; s++) {

			masterBuffer.at(s) += channelBuffer.at(s);

		}

	}

	// Apply post processing.


	// Finally assign stream var to the audio data.

	// Recast back to Int16.
	// Since we're directly assigning the elements in "samples"
	// there's no need to clear the vector.
	for (int s = 0; s < bufferSize; s++) { samples.at(s) = masterBuffer.at(s); }

	data.samples = &samples;
	data.sampleCount = bufferSize;
	return true;

}*/