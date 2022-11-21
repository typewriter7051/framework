#include "../../nn_module.h"

class TestModule : public NNModule {
public:
    TestModule() {}
    TestModule(int size) {
	nums = std::vector<float>(size);
    }

    const std::vector<float>* getOutputs() override;
    void initializeParameters(float min, float max) override;

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(const std::vector<float>* derivs, float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // This is where the actual processing is done.
    void process(const std::vector<float>* inputs) override;

    std::vector<float> nums;
};
