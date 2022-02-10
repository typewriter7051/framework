#pragma once
#include <memory>
#include "neuron.h"

namespace AI {

	class NeuronPos {
	public:

		float x, y;

		void move(float a, float b) {

			x += a;
			y += b;

		}

	};

}

class TrainingNeuron : public Neuron {
public:

    TrainingNeuron();

    //--------------------------------------------------------------------------------
	// Getters and setters.

	AI::NeuronPos getPos() { return pos; }
	void setPos(AI::NeuronPos p) { pos = p; }

    unsigned int getNumConnections();

    float getBias();
	void setBias(float b);

	void setConnections(std::vector<float> values, float strength);
	void addConnections(std::vector<float> values, float strength);

    // Randomizes weights.
	void setupAverageConnections(float min, float max);

    //--------------------------------------------------------------------------------
	// File handling.

	void saveConnectionsStatus(std::ofstream* file);

    //--------------------------------------------------------------------------------
	// Misc.

	void clearValues();

private:

	AI::NeuronPos pos;

};
