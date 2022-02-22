#include "tnn.h"

// Creates a typical CNN with a series a hidden layers consistent in size.
TrainingNeuralNetwork createConvolutionalNetwork(int inputs, int outputs, int hidden, int hiddenLayers);

// look up technical term later.
TrainingNeuralNetwork createUnevenNetwork(std::vector<int> sizes);