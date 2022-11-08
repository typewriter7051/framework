#include "nn_module.h"

NNModule::NNModule() {}

const std::vector<float>* NNModule::getOuptuts() {
    return outputs;
}