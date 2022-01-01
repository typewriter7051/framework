#include "../../ui/ui.h"
#include "nn.h"

// Draws neuron AV vs theoretical minimum AV.
void drawNeuronPreformance(std::vector<float> samplePoints, std::vector<float> minAVs, sf::FloatRect dimensions, Window* window) {



}

void drawNeuronCost(NeuralNetwork* nn, sf::FloatRect dimensions, Window* window) {



}

class NNMonitor : public Scene {
public:

    virtual void drawBehindUI(std::shared_ptr<sf::RenderWindow> window) {



	}

	virtual void drawAheadUI(std::shared_ptr<sf::RenderWindow> window) {



	}

	virtual void process(MouseState& ms, double timePassed) {



	}

	virtual void eventHandle(sf::Event& event) {



	}

private:

    NeuralNetwork nn;
    std::string name;

};
