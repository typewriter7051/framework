#include "nn_module.h"

void NNModule::NNModule() {
    timesCalled = 0;
}

std::vector<float>* NNModule::getOuptuts() {
    return &outputs;
}