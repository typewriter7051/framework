#include "dynamic_nn.h"

// Creates a typical CNN with a series a hidden layers consistent in size.
DynamicNeuralNetwork* createConvolutionalNetwork(int inputs, int outputs, int hidden, int hiddenLayers);

// look up technical term later.
DynamicNeuralNetwork* createUnevenNetwork(std::vector<int> sizes);