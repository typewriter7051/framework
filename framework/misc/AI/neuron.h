#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <vector>

class Neuron {
public:

	//--------------------------------------------------------------------------------
	// Constructors.

	Neuron();

	//--------------------------------------------------------------------------------
	// Getters & setters.

	float getValue();

	unsigned int getID();

	std::vector<Neuron*> getConnections();

	void setValue(float f);

	void setDone();
	void setUndone();

	void addConnection(Neuron* n);
	void addConnection(Neuron* n, float w);

	static void resetIDCounter();

protected:

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

	enum NonLinearMethod {identity, step, sigmoid, hyperTan, ELU, RELU, swish};
	NonLinearMethod af;

	std::vector<float> values;

	//--------------------------------------------------------------------------------
	// Neural connection struct.

	struct NeuralConnection {
	public:

		Neuron* prevNeuron;
		float weight;

		NeuralConnection() : weight(0), prevNeuron(NULL) {}
		NeuralConnection(Neuron* n) : weight(0) { prevNeuron = n; }
		NeuralConnection(Neuron* n, float w) : weight(w) { prevNeuron = n; }
		//~NeuralConnection() { delete prevNeuron; prevNeuron = NULL; }

		float retrieveValue() {

			return prevNeuron->getValue() * weight;

		}

	};

	//--------------------------------------------------------------------------------

	std::vector<NeuralConnection> ncs;

};
