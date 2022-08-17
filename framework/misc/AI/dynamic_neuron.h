#pragma once
#include <memory>
#include <fstream>
#include <vector>

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

namespace ActivationFunction {

	enum NonLinearMethod {
		arcHyperTan,
		ELU,
		hyperTan,
		identity,
		mish,
		ReLU,
		step,
		sigmoid,
		softplus,
		swish
	};

}

class DynamicNeuron {
public:

    DynamicNeuron();

    //--------------------------------------------------------------------------------
	// Getters and setters.

	AI::NeuronPos getPos() { return pos; }
	void setPos(AI::NeuronPos p) { pos = p; }

    unsigned int getNumConnections();

	void addConnection(DynamicNeuron* n);
	void addConnection(DynamicNeuron* n, float w);

	unsigned int getID();

	DynamicNeuron* getChild(int i);

    float getBias();
	void setBias(float b);

	float getValue();
	void setValue(float f);

	void setUndone();
	void setDone();

	void getDerivative(std::vector<int>* countRecord, std::vector<std::vector<float>>* derivRecord, float dcost);

	void moveWeight(int index, float value);
	void moveMembers(std::vector<float>* values, float strength);

	void setActivationFunction(ActivationFunction::NonLinearMethod method);

    // Randomizes weights.
	void setupAverageConnections(float min, float max);

	//--------------------------------------------------------------------------------
	// Neural connection struct.

	struct DynamicNeuralConnection {
	public:

		DynamicNeuron* prevNeuron;
		float weight;
		bool isRecursive;

		DynamicNeuralConnection() {}
		DynamicNeuralConnection(DynamicNeuron* n) { prevNeuron = n; }
		DynamicNeuralConnection(DynamicNeuron* n, float w) { prevNeuron = n; weight = w; }
		//~NeuralConnection() { delete prevNeuron; prevNeuron = NULL; }

		float retrieveValue(bool incrementParent) {

			if (!isRecursive && incrementParent) prevNeuron->numParents++;
			return prevNeuron->getValue() * weight;

		}

	};

	//--------------------------------------------------------------------------------
	// numParents

	unsigned int numParents; // Number of parent neuron connections in the network.

	void incrementParent();

	bool isComplete(unsigned int np);

	void resetNumParents();

    //--------------------------------------------------------------------------------
	// File handling.

	void saveConnectionsStatus(std::ofstream* file);

    //--------------------------------------------------------------------------------
	// Misc.

	void clearValues();

	static void resetIDCounter();

private:

	float getAVDerivative();

	void applyNonlinear();

	bool finished;
	static unsigned int idCounter;
	unsigned int ID;
	float av;
	float bias;
	ActivationFunction::NonLinearMethod af;
	std::vector<float> values;
	AI::NeuronPos pos;

	std::vector<DynamicNeuralConnection> ncs;

};