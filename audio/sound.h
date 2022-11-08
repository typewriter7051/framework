#include <vector>
#include <algorithm>		// for std::fill
#include <SFML/Audio.hpp>

//https://www.sfml-dev.org/tutorials/2.5/audio-streams.php

namespace Sound {

	class Channel;

	class Synth {
	public:

		std::vector<float>* getBuffer(unsigned int numSamples);

	protected:

		virtual void generateBuffer() = 0;

		std::vector<float> samples;

	private:
		
		std::shared_ptr<Channel> channel;

	};

	class Effect {

	public:

		void processBufferAndMix(std::vector<float>& b);

	protected:

		virtual void processBuffer(std::vector<float>&) = 0;

		float mix, gain;

		std::vector<float> drySamples;

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

		std::vector<float>* processBuffer(std::vector<float>& buffer);

	private:
		// Holds a list of all the desired sound effects on the channel.
		std::vector<std::shared_ptr<Effect>> effects;

		std::vector<float> samples;

	};

	class SoundHandler : public sf::SoundStream {
	public:

		SoundHandler() {

			bufferSize = 2048;
			convertedSamples.resize(bufferSize);
			masterSamples.resize(bufferSize);

			numChannels = 2;
			sampleRate = 44100;

			initialize(numChannels, sampleRate);

			// Push out a blank channel as master.
			channels.push_back(Channel(bufferSize));

		}

		/*

		On getData() call:

		-iterate through list of generators and call generateBuffer();

		-sum them up into a single list

		-apply post process

		-THEN set the data.samples pointer after all is done.

		*/

	private:

		void onSeek(sf::Time timeOffset) override {}

		bool onGetData(Chunk& data) override;

		std::vector<std::shared_ptr<Synth>> synths;

		// Holds all the channels that are playing sound.
		std::vector<Channel> channels;

		std::vector<sf::Int16> convertedSamples;
		std::vector<float> masterSamples;

		unsigned int numChannels;
		unsigned int sampleRate;
		unsigned int bufferSize;

	};

}