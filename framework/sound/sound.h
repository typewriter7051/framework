#include <vector>
#include <algorithm>		// for std::fill
//#include <SFML/Audio.hpp>

//https://www.sfml-dev.org/tutorials/2.5/audio-streams.php

namespace sound {

	class Synth {

		Channel* channel;

		std::vector<float> samples;

		std::vector<float>* getBuffer(unsigned int numSamples) {}

		std::vector<float>* generateBuffer() = 0;

	};

	class Effect {

		float mix, gain;

		std::vector<float> samples;

	public:

		void processAndHandleBuffer(std::vector<float>& b) {}

		void processBuffer(std::vector<float>&) = 0;

	};

	// Acts as a track in a DAW
	class Channel {
	public:

		Channel() {

			samples.resize(2048);
			std::fill(samples.begin(), samples.end(), 0);

		}

		Channel(unsigned int bufferSize) {

			samples.resize(bufferSize);

		}

		/*
		
		-copy synth data to the new "samples" vector

		-iterate through and apply all effects

		-return pointer to "samples"
		
		*/

		std::vector<float>* processBuffer(std::vector<float>& buffer) {}

	private:
		// Holds a list of all the desired sound effects on the channel.
		std::vector<Effect> effects;

		std::vector<float> samples;

	};

	/*

	On getData() call:

		-iterate through list of generators and call generateBuffer();

		-sum them up into a single list

		-apply post process

		-THEN set the data.samples pointer after all is done.

	*/

	/*class SoundHandler : public sf::SoundStream {
	public:

		SoundHandler() {

			bufferSize = 2048;
			samples.resize(bufferSize);
			initialize(numChannels, sampleRate);

			// Push out a blank channel as master.
			channels.push_back(Channel(bufferSize));

		}

		bool onGetData(Chunk& data) override {}

		void onSeek(sf::Time timeOffset) override;

	private:

		// Holds all the channels that are playing sound.
		std::vector<Channel> channels;

		std::vector<SoundGenerator*> synths;

		std::vector<sf::Int16> samples;

		unsigned int numChannels;
		unsigned int sampleRate;
		unsigned int bufferSize;

	};*/

}