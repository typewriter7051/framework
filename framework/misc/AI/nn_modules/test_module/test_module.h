#include "../../nn_module.h"

class TestModule : public NNModule {
public:
    TestModule() {}
    TestModule(int size) {
        nums.resize(size);
        outputs = &nums;
    }

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void trainModule(std::vector<float>* derivs) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // This is where the actual processing is done.
    void process() override;

    std::vector<float> nums;
};