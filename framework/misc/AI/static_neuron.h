#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <vector>

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

class StaticNeuron {
public:

	//--------------------------------------------------------------------------------
	// Constructors.

	StaticNeuron();

	//--------------------------------------------------------------------------------
	// Getters & setters.

	float getValue();

	unsigned int getID();

	std::vector<StaticNeuron*> getConnections();

	void setValue(float f);
	void moveValue(float f, float strength);

	void setBias(float b);
	void moveBias(float b);

	void setActivationFunction(ActivationFunction::NonLinearMethod a);

	void setDone();
	void setUndone();

	void addConnection(StaticNeuron* n);
	void addConnection(StaticNeuron* n, float w);

	static void resetIDCounter();

private:

	void applyNonlinear();

	// Shows whether dependencies have already been satisfied or not.
	bool finished;

	// Static var used for keeping track of how many neuron objects there are.
	static unsigned int idCounter;

	// Global neuron ID.
	unsigned int ID;

	// Activation Value.
	float av;
	float bias;

	ActivationFunction::NonLinearMethod af;

	std::vector<float> values;

	//--------------------------------------------------------------------------------
	// Neural connection struct.

	struct NeuralConnection {
	public:

		float weight;
		bool isRecursive;

		NeuralConnection() : weight(0), isRecursive(false), prevNeuron(NULL) {}
		NeuralConnection(StaticNeuron* n) : weight(0), isRecursive(false) { prevNeuron = n; }
		NeuralConnection(StaticNeuron* n, float w) : weight(w), isRecursive(false) { prevNeuron = n; }
		//~NeuralConnection() { delete prevNeuron; prevNeuron = NULL; }

		float retrieveValue() {

			return prevNeuron->getValue() * weight;

		}

		StaticNeuron* getPrevNeuron() { return prevNeuron; }

	private:

		StaticNeuron* prevNeuron;

	};

	std::vector<NeuralConnection> ncs;

};
