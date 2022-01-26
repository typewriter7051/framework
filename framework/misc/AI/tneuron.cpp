#include "tneuron.h"
#include <random>

TrainingNeuron::TrainingNeuron() {

	// No need to do ID handling or anything since it's
	// included in the parent class' constructor.

}

//================================================================================
// Getters & setters.

unsigned int TrainingNeuron::getNumConnections() {

	return ncs.size();

}

float TrainingNeuron::getBias() {

	return bias;

}

void TrainingNeuron::setBias(float b) {

	bias = b;

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

	//std::cout << "\nSize: " << size << std::endl;

	for (NeuralConnection nc : ncs) {

		//*file << nc.prevNeuron->getID() << "\n" << nc.weight << "\n";
		unsigned int ID = nc.prevNeuron->getID();
		file->write((char*) &ID, sizeof(unsigned int));
		file->write((char*) &nc.weight, sizeof(float));

		//std::cout << "to: " << ID << std::endl;
		//std::cout << "weight: " << nc.weight << std::endl;

	}

}

//================================================================================
// Misc.

void TrainingNeuron::clearValues() {

	values.clear();

}
