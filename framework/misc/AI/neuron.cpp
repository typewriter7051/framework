#include "neuron.h"
#include <random>
#include <time.h>
#include <memory>

// Static member definition.
unsigned int Neuron::idCounter = 0;

//================================================================================
// Constructors.

Neuron::Neuron() {

	ID = idCounter;
	idCounter++;

	av = 0;
	finished = false;
	bias = 0;

}

float Neuron::getValue() {

	float temp = 0;

	if (finished)
		return av;

	else {

		// Mark the node as "done" in case future nodes wish to retrieve its value.
		// It's important to keep this before the for loop to avoid infinite recursion.
		finished = true;

		for (int nc = 0; nc < ncs.size(); nc++) {

			// Weight multiplication is already done in retrieveValue().
			temp += ncs[nc].retrieveValue();

		}

	}

	// Add bias and apply nonlinear transform.
	av = temp + bias;
	applyNonlinear();

	return av;

}

void Neuron::applyNonlinear() {

	av = tanh(av);

}
