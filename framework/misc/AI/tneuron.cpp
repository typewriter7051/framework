#include "tneuron.h"
#include <random>
#include <cmath> // For inverseNonlinear()

using namespace ActivationFunction;

TrainingNeuron::TrainingNeuron() {

	// No need to do ID handling or anything since it's
	// included in the parent class' constructor.

	// Placeholder.
	pos.x = 10;
	pos.y = 10;

}

//================================================================================
// Getters & setters.

unsigned int TrainingNeuron::getNumConnections() {

	return ncs.size();

}

float TrainingNeuron::getBias() {

	return bias;

}

void TrainingNeuron::setBias(float b, float strength) {

	bias = strength * b + (1 - strength) * bias;

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

void TrainingNeuron::addConnections(std::vector<float> values, float strength) {

	if (values.size() != ncs.size()) {

		std::cout << "YOU STUPID";
		return;

	}

	for (int val = 0; val < ncs.size(); val++) {

		ncs[val].weight += values[val] * strength;

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

float TrainingNeuron::nonLinear(float v) {

	switch (af) {

	case identity:; break;
	case step: v = (v < 0) ? 0 : 1; break;
	case sigmoid: v = 1 / (1 + exp(-v)); break;
	case hyperTan: v = tanh(v); break;
	case ELU: v = (v < 0) ? exp(v) - 1 : v; break;
	default:; break;

	}

	return v;

}

float TrainingNeuron::inverseNonlinear(float v) {

	switch (af) {

	case identity:; break;
	case step: v = (v < 0) ? -1 : 1; break;
	case sigmoid: v = -log(1 / v - 1); break;
	case hyperTan: v = atanh(v); break;
	case ELU: v = (v < 0) ? log(v + 1) : v; break;
	default:; break;

	}

	return v;

}
