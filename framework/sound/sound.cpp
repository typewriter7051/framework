#include "sound.h"

std::vector<float>* sound::Synth::getBuffer(unsigned int numSamples) {

	// detect change in sample rate.
	if (samples.size() != numSamples) samples.resize(numSamples);

	generateBuffer();

	return channel->processBuffer(samples);

}

void sound::Effect::processBufferAndMix(std::vector<float>& b) {

	drySamples = b;

	processBuffer(b);

	for (int i = 0; i < b.size(); i++) {

		// Apply mix and gain.
		b.at(i) = (mix * b.at(i) + (1 - mix) * drySamples.at(i)) * gain;

	}

}

std::vector<float>* sound::Channel::processBuffer(std::vector<float> & buffer) {

	samples = buffer;

	for (std::shared_ptr<Effect> e : effects) {

		e->processBufferAndMix(samples);

	}

	return &samples;

}

bool sound::SoundHandler::onGetData(Chunk& data) {

	// Clear the master channel.
	std::fill(masterSamples.begin(), masterSamples.end(), 0);

	std::vector<float>* tempSamples;

	for (std::shared_ptr<Synth> s : synths) {

		tempSamples = s->getBuffer(bufferSize);

		for (int i = 0; i < masterSamples.size(); i++) { masterSamples.at(i) += tempSamples->at(i); }

	}

	// Master channel processing.
	channels.at(0).processBuffer(masterSamples);

	for (float s : masterSamples) {

		// Basic clipping if all else fails.
		if (s > 1) s = 1;
		else if (s < -1) s = -1;

	}

	for (int i = 0; i < bufferSize; i++) {

		// Convert to sf::Int16 and store in the convertedSamples vector.
		convertedSamples.at(i) = masterSamples.at(i) * UINT16_MAX;

	}

	data.samples = &convertedSamples.at(0);
	data.sampleCount = bufferSize;

	return true;

}