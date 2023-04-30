#include "test_module.h"
//==============================================================================

void TestModule::initializeParameters(float min, float max) {
}
//==============================================================================

void TestModule::process() {
    for (int i = 0; i < size; i++) {
        outputs[i] += inputs[i];
    }
}
//==============================================================================

void TestModule::train(float stepSize) {
    for (int i = 0; i < size; i++) {
        derivInputs[i] += derivOutputs[i];
    }
}
//==============================================================================

void TestModule::saveToFile(std::ofstream* file) {
    // Nothing to do here...
}

void TestModule::readFromFile(std::ifstream* file) {
    // Nothing to do here...
}
