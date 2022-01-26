#include <vector>
#include "templates.h"

// Creates a typical CNN with a series a hidden layers consistent in size.
TrainingNeuralNetwork createConvolutionalNetwork(int inputs, int outputs, int hidden, int hiddenLayers) {

	TrainingNeuralNetwork nn;

	unsigned int hiddenNeurons = hidden * hiddenLayers;
	int hiddenStart = inputs + outputs;
	nn.setNeurons(inputs, outputs, hiddenNeurons);

	// Connect the hidden neurons.
	for (int l = 0; l < hiddenLayers - 1; l++) {

		std::vector<Neuron*> parentLayer, childLayer;

		int childStart = hiddenStart + l * hidden;
		int childEnd = childStart + hidden - 1;
		int parentStart = childStart + hidden;
		int parentEnd = childEnd + hidden;

		childLayer = nn.getArray(childStart, childEnd);
		parentLayer = nn.getArray(parentStart, parentEnd);

		nn.fullyConnectNeurons(parentLayer, childLayer);

	}

	// Connect first hidden layer to input layer.
	nn.fullyConnectNeurons(nn.getArray(hiddenStart, hiddenStart + hidden - 1), nn.getInputs());

	// Connect output layer to last hidden layer.
	int lastStart = hiddenStart + (hiddenLayers - 1) * hidden;
	int lastEnd = lastStart + hidden - 1;
	nn.fullyConnectNeurons(nn.getOutputs(), nn.getArray(lastStart, lastEnd));

	// Return the fully set up network.
	return nn;

}