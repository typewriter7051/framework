#include "test_module.h"
//==============================================================================

c_vecp TestModule::getOutputs() {
    return &nums;
}

void TestModule::initializeParameters(float min, float max) {
}
//==============================================================================

void TestModule::process(c_vecp inputs) {
    for (int i = 0; i < inputs->size(); i++) {
        nums.at(i) = inputs->at(i);
    }
}
//==============================================================================

c_vecp TestModule::train(c_vecp derivs, float stepSize) {
    // Just pass down the derivs pointer.
    return derivs;
}
//==============================================================================

void TestModule::saveToFile(std::ofstream* file) {
    // Nothing to do here...
}

void TestModule::readFromFile(std::ifstream* file) {
    // Nothing to do here...
}
