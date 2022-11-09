#include "test_module.h"
#include <iostream>
//==============================================================================

void TestModule::process(const std::vector<float>* inputs) {
    //if (inputs->size() != nums.size()) return;
    for (int i = 0; i < inputs->size(); i++) {
	std::cout << i << "out of " << inputs->size() << " and " << nums.size() << std::endl;
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
