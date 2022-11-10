#include "nn_module.h"

NNModule::NNModule() {
    outputs = NULL;
}

const std::vector<float>* NNModule::getOutputs() {
    return outputs;
}
