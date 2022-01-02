#include "tneuron.h"

TrainingNeuron::TrainingNeuron() {

	ID = idCounter;
	idCounter++;

	av = 0;
	finished = false;
	bias = 0;

}

//================================================================================
// Getters & setters.

unsigned int TrainingNeuron::getID() {

	return ID;

}

unsigned int TrainingNeuron::getNumConnections() {

	return ncs.size();

}

std::vector<Neuron*> TrainingNeuron::getConnections() {

	std::vector<Neuron*> returnList;

	for (NeuralConnection nc : ncs) {

		returnList.push_back(nc.prevNeuron);

	}

	return returnList;

}

float TrainingNeuron::getBias() {

	return bias;

}

void TrainingNeuron::setBias(float b) {

	bias = b;

}

void TrainingNeuron::setValue(float f) {

	av = f;

	// Ensures that the neuron directly returns activation value without calling connected neurons.
	finished = true;

}

// Clears finished status for next iteration.
void TrainingNeuron::setUndone() {

	finished = false;

}

void TrainingNeuron::setDone() {

	finished = true;

}

void TrainingNeuron::setupAverageConnections(float min, float max) {

	std::mt19937 rng;
	std::unique_ptr<std::uniform_real_distribution<float>> dis;
	dis = std::make_unique<std::uniform_real_distribution<float>>(min, max);

	for (int nc = 0; nc < ncs.size(); nc++) {

		rng.seed(ID * ncs[nc].prevNeuron->getID());
		ncs[nc].weight = (*dis)(rng);

	}

}

void TrainingNeuron::setConnections(std::vector<float> values, float strength) {

	if (values.size() != ncs.size()) {

		std::cout << "YOU STUPID";
		return;

	}

	for (int val = 0; val < ncs.size(); val++) {

		ncs[val].weight = ncs[val].weight * (1 - strength) + values[val] * strength;

	}

}

//================================================================================
// File handling.

void TrainingNeuron::saveConnectionsStatus(std::ofstream* file) {

	//*file << ncs.size() << "\n";
	int size = ncs.size();
	file->write((char*) &size, sizeof(int));

	for (NeuralConnection nc : ncs) {

		//*file << nc.prevNeuron->getID() << "\n" << nc.weight << "\n";
		unsigned int ID = nc.prevNeuron->getID();
		file->write((char*) &ID, sizeof(unsigned int));
		file->write((char*) &nc.weight, sizeof(float));

	}

}

//================================================================================
// Misc.

void Neuron::addConnection(Neuron* n) {

	ncs.push_back(NeuralConnection(n));

}

void Neuron::addConnection(Neuron* n, float w) {

	ncs.push_back(NeuralConnection(n, w));

}

void Neuron::clearValues() {

	values.clear();

}

void Neuron::resetIDCounter() {

	idCounter = 0;

}
