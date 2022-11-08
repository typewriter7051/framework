#pragma once
#include <memory>
#include <fstream>
#include <vector>
#include <iostream>

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
	void addConnection(DynamicNeuron* n, bool isRecursive);
	void addConnection(DynamicNeuron* n, float w);

	unsigned int getID();

    float getBias();
	void setBias(float b);

	float getValue( std::vector<float>* profile, std::vector<float>* oldProfile, std::vector<bool>* completionRecord);

	float getAvgConnection();

	void getDerivative( std::vector<float>* profile, std::vector<int>* countRecord, std::vector<std::vector<float>>* derivRecord, float dcost);

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

		DynamicNeuralConnection() { isRecursive = false; }
		DynamicNeuralConnection(DynamicNeuron* n) { prevNeuron = n; isRecursive = false; }
		DynamicNeuralConnection(DynamicNeuron* n, bool r) { prevNeuron = n; isRecursive = r; }
		DynamicNeuralConnection(DynamicNeuron* n, float w) { prevNeuron = n; weight = w; isRecursive = false; }
		//~NeuralConnection() { delete prevNeuron; prevNeuron = NULL; }

		void incrementChildParent(std::vector<bool>* completionRecord) {

			prevNeuron->numParents += !isRecursive; // Branchless version.
			//if (!isRecursive) prevNeuron->numParents++;
			prevNeuron->incrementChildParents(completionRecord);

		}

	};

	//--------------------------------------------------------------------------------
	// numParents

	void incrementChildParents(std::vector<bool>* completionRecord);

	unsigned int numParents; // Number of parent neuron connections in the network.
	void resetNumParents();

    //--------------------------------------------------------------------------------
	// File handling.

	void saveConnectionsStatus(std::ofstream* file);

    //--------------------------------------------------------------------------------
	// Misc.

	static void resetIDCounter();

	void decrementID();
	void decrementConnections(unsigned int ID);
	void removeConnection(unsigned int neuronID);
	void removeDeadConnections(float threshold);

	std::vector<DynamicNeuralConnection> ncs;

private:

	float getAVDerivative(std::vector<float>* profile);
	void applyNonlinear(std::vector<float>* profile);

	static unsigned int idCounter;
	unsigned int ID;
	float bias;
	ActivationFunction::NonLinearMethod af;
	AI::NeuronPos pos;

};