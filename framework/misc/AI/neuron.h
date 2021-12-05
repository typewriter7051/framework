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

	unsigned int getNumConnections();

	std::vector<Neuron*> getConnections();

	float getBias();
	void setBias(float b);

	void setValue(float f);

	void setUndone();
	void setDone();

	// Randomizes weights.
	void setupAverageConnections(float min, float max);

	void setConnections(std::vector<float> values, float strength);

	//--------------------------------------------------------------------------------
	// File handling.

	void saveConnectionsStatus(std::ofstream* file);

	//--------------------------------------------------------------------------------
	// Misc.

	void addConnection(Neuron* n);
	void addConnection(Neuron* n, float w);

	void clearValues();

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