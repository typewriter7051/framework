#include "test_module.h"
//==============================================================================

const std::vector<float>* TestModule::getOutputs() {
    return &nums;
}
//==============================================================================

void TestModule::process(const std::vector<float>* inputs) {
    for (int i = 0; i < inputs->size(); i++) {
        nums.at(i) = inputs->at(i);
    }
}
//==============================================================================

void TestModule::train(const std::vector<float>* derivs, float stepSize) {

}
//==============================================================================

void TestModule::saveToFile(std::ofstream* file) {

}

void TestModule::readFromFile(std::ifstream* file) {

}
