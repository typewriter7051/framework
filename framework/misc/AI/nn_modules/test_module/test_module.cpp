#include "test_module.h"
//==============================================================================

void TestModule::process(const std::vector<float>* inputs) {
    for (int i = 0; i < inputs.size() i++) {
        outputs[i] = inputs->at(i);
    }
}
//==============================================================================

void TestModule::train(const std::vector<float>* derivs) {

}
//==============================================================================

void TestModule::saveToFile(std::ofstream* file) {

}

void TestModule::readFromFile(std::ifstream* file) {

}