#include <vector>
#include "templates.h"

//==============================================================================
// Fully connected dense network with a set number of hidden layers and neurons.

// Creates a typical CNN with a series a hidden layers consistent in size.
DynamicNeuralNetwork* createConvolutionalNetwork(int inputs, int outputs, int hidden, int hiddenLayers) {

	DynamicNeuralNetwork* nn = new DynamicNeuralNetwork();

	unsigned int hiddenNeurons = hidden * hiddenLayers;
	int hiddenStart = inputs + outputs;
	nn->setNeurons(inputs, outputs, hiddenNeurons);

	// If there are no hidden neurons (why would anyone do this).
	if (hiddenLayers == 0 || hidden == 0) {

		nn->fullyConnectNeurons(nn->getOutputs(), nn->getInputs());
		return nn;

	}

	// Connect the hidden neurons.
	for (int l = 0; l < hiddenLayers - 1; l++) {

		std::vector<DynamicNeuron*> parentLayer, childLayer;

		int childStart = hiddenStart + l * hidden;
		int childEnd = childStart + hidden;
		int parentStart = childStart + hidden;
		int parentEnd = childEnd + hidden;

		childLayer = nn->getArray(childStart, childEnd);
		parentLayer = nn->getArray(parentStart, parentEnd);

		nn->fullyConnectNeurons(parentLayer, childLayer);

	}

	// Connect first hidden layer to input layer.
	nn->fullyConnectNeurons(nn->getArray(hiddenStart, hiddenStart + hidden - 1), nn->getInputs());

	// Connect output layer to last hidden layer.
	int lastStart = hiddenStart + (hiddenLayers - 1) * hidden;
	int lastEnd = lastStart + hidden - 1;
	nn->fullyConnectNeurons(nn->getOutputs(), nn->getArray(lastStart, lastEnd));

	// Return the fully set up network.
	return nn;

}

//==============================================================================
// Fully connected, but each layer has a custom size.

// List of layer sizes.
DynamicNeuralNetwork* createUnevenNetwork(std::vector<int> sizes) {

	DynamicNeuralNetwork* nn = new DynamicNeuralNetwork();

	// Not enough layers to make a neural network.
	if (sizes.size() < 2) return nn;

	int in = sizes.at(0);
	int on = sizes.back();
	int hn = 0;

	// Exactly 2 layers in the neural network (input and output).
	if (sizes.size() == 2) {

		nn->setNeurons(in, on, 0);
		nn->fullyConnectNeurons(nn->getOutputs(), nn->getInputs());
		return nn;

	}

	for (int n = 1; n < sizes.size() - 1; n++)
		hn += sizes.at(n);

	nn->setNeurons(in, on, hn);

	int index = in + on;
	// Connect first hidden layer to input layer.
	nn->fullyConnectNeurons(nn->getArray(index, index + sizes.at(1) - 1), 
						    nn->getInputs());
	// Connect output layer to last hidden layer.
	nn->fullyConnectNeurons(nn->getOutputs(),
						    nn->getArray(in + on + hn - 1 - sizes.at(sizes.size() - 2),
									     in + on + hn - 1));

	for (int n = 1; n < sizes.size() - 1; n++) {

		std::vector<DynamicNeuron*> cur  = nn->getArray(index, index + sizes.at(n) - 1);
		std::vector<DynamicNeuron*> next = nn->getArray(index + sizes.at(n), index + sizes.at(n) + sizes.at(n + 1) - 1);

		nn->fullyConnectNeurons(next, cur);

		index += sizes.at(n);

	}

	return nn;

}

//==============================================================================
// Each neuron has exactly 2 connections.
// This is most commonly used for audio.

DynamicNeuralNetwork* createWavenet(int bufferSize, int hiddenLayers) {

	if ((bufferSize & (bufferSize - 1)) == 0 || (bufferSize >> hiddenLayers) < 1) {

		std::cout << "\nWARNING: createWavenet() called with invalid size!";
		return NULL;

	}

	int in = bufferSize;
	int on = bufferSize;
	int hn = bufferSize * hiddenLayers;

	DynamicNeuralNetwork* nn = new DynamicNeuralNetwork();
	nn->setNeurons(in, on, hn);
	std::vector<DynamicNeuron*> neurons = nn->getNeurons();

	if (hiddenLayers == 0) {

		// Straight connections.
		for (int i = in; i < in + on; i++)
			nn->connectNeurons(i, i - in, false);

		// Diagonal connections.
		for (int i = in + 1; i < in + on; i++)
			nn->connectNeurons(i, i - in - 1, false);

		// Only 1 recursive connection.
		nn->connectNeurons(in, in - 1, true);

		return nn;

	}

	// Straight connections.

	// Output layer + hidden layers.
	for (int i = on; i < in + hn; i++)
		nn->connectNeurons(i, i + bufferSize, false);

	// Input layer.
	for (int i = in + hn; i < in + hn + on; i++)
		nn->connectNeurons(i, i - in - hn, false);

	// Diagonal connections.

	// First layer
	for (int i = on + hn + 1; i < in + on + hn; i++)
		nn->connectNeurons(i, i - on - hn - 1, false);
	nn->connectNeurons(on + hn, in - 1, true);

	for (int l = 1; l <= hiddenLayers; l++) {

		int shift = 1 << l; // 2^l
		int index = in + on + hn - (l + 1) * in;

		for (int i = shift; i < bufferSize; i++)
			nn->connectNeurons(index + i, index + bufferSize + i - shift, false);

		for (int i = 0; i < shift; i++)
			nn->connectNeurons(index + i, index + bufferSize + bufferSize + i - shift, true);

	}

	return nn;

}