#include <algorithm> // For std::fill()

void NNModule::NNModule() {
    timesCalled = 0;
}
//==============================================================================

int NNModule::getNumInputs() {
    return inputs->size();
}

int NNModule::getNumOutputs() {
    return outputs->size();
}
//==============================================================================

void NNModule::setIOPtrs(std::vector<float>* i, std::vector<float>* o) {
    inputs = i;
    outputs = o;

    inputDerivs.resize(i.size());
    outputDerivs.resize(o->size());
}
//==============================================================================

void NNModule::firstCall() {
    return timesCalled == 1;
}

void NNModule::lastCall() {
    return timesCalled == numParents;
}
//==============================================================================

void NNModule::trainModule(std::vector<float>* derivs) {
    timesCalled++;
    // Reset derivative lists on first call.
    if (firstCall()) {
        std::fill(inputDerivs.begin(), inputDerivs.end(), 0);
        std::fill(outputDerivs.begin(), outputDerivs.end(), 0);
    }
    // Add derivs onto outputDerivs.
    for (float f : derivs)
        outputDerivs += f;
    // If all dependencies are solved then pass to train() and train child modules.
    if (lastCall()) {
        train(&outputDerivs);

        for (NNModule* cm : childModules)
            cm->trainModule(&inputDerivs);
    }
}
//==============================================================================

// TODO: this alg doesn't work with 2 inputs 1 output!
void NNModule::updateValues() {
    // Prevents the module from being run twice.
    timesCalled++;
    if (!firstCall()) return;

    for (NNModule* cm : childModules)
        cm->updateValues();
    
    process(inputs, outputs);
}
//==============================================================================

void NNModule::callReset() {
    timesCalled = 0;
    reset();
}