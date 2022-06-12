#pragma once
#include <memory>
#include <fstream>

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

class TrainingNeuron {
public:

    TrainingNeuron();

    //--------------------------------------------------------------------------------
	// Getters and setters.

	// The TrainingNeuron version of getValue(). This includes additional features such as
	// incrementing the numParents value depending on the connection type.
	float getValue(bool recurse);

	AI::NeuronPos getPos() { return pos; }
	void setPos(AI::NeuronPos p) { pos = p; }

    unsigned int getNumConnections();

	void addConnection(TrainingNeuron* n);
	void addConnection(TrainingNeuron* n, float w);

	unsigned int getID();

	TrainingNeuron* getChild(int i);

    float getBias();
	void setBias(float b);

	float getValue(bool recurse);
	void setValue(float f);

	void setUndone();
	void setDone();

	void getDerivative(std::vector<int>* countRecord, std::vector<float>* derivRecord, float dcost);

	void moveWeight(int index, float value);
	void moveMembers(std::vector<float>* values, float strength);

	void setActivationFunction(ActivationFunction::NonLinearMethod method);

    // Randomizes weights.
	void setupAverageConnections(float min, float max);

	//--------------------------------------------------------------------------------
	// Neural connection struct.

	struct TrainingNeuralConnection {
	public:

		TrainingNeuron* prevNeuron;
		float weight;
		bool isRecursive;

		TrainingNeuralConnection() {}
		TrainingNeuralConnection(TrainingNeuron* n) { prevNeuron = n; }
		TrainingNeuralConnection(TrainingNeuron* n, float w) { prevNeuron = n; weight = w; }
		//~NeuralConnection() { delete prevNeuron; prevNeuron = NULL; }

		float retrieveValue() {

			return prevNeuron->getValue(!isRecursive) * weight;

		}

	};

	//--------------------------------------------------------------------------------
	// numParents

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

	unsigned int numParents; // Number of parent neuron connections in the network.

	float dCost; // Derivative of the cost with respect to this neuron's activation value.

	std::vector<TrainingNeuralConnection> ncs;

};
