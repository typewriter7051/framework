#include "../../module.h"

class TestModule : public Module {
public:
    TestModule() : size(0) {}
    TestModule(int _size) {
        size = _size;
    }

    void initializeParameters(float min, float max) override;

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // This is where the actual processing is done.
    void process() override;

    float size;
};
