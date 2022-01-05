#include "neuron.h"

class TrainingNeuron : public Neuron {
public:

    TrainingNeuron();

    //--------------------------------------------------------------------------------
	// Getters and setters.

    unsigned int getNumConnections();

    float getBias();
	void setBias(float b);

	void setConnections(std::vector<float> values, float strength);

    // Randomizes weights.
	void setupAverageConnections(float min, float max);

    //--------------------------------------------------------------------------------
	// File handling.

	void saveConnectionsStatus(std::ofstream* file);

    //--------------------------------------------------------------------------------
	// Misc.

	void clearValues();

private:



};
