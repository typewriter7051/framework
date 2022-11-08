#include "../../nn_module.h"

class TestModule : public NNModule {
public:
    TestModule() {}
    TestModule(int size) {
        nums.resize(size);
        outputs = &nums;
    }

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(const std::vector<float>* derivs, float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // This function can be private because the base function was declared as public.
    // This is where the actual processing is done.
    void process(const std::vector<float>* inputs) override;

    std::vector<float> nums;
};
