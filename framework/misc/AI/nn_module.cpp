// TODO: this alg doesn't work with 2 inputs 1 output!
void NNModule::updateValues() {
    // Prevents the module from being run twice.
    if (alreadyUpdated) return;
    alreadyUpdated = true;

    for (NNModule* cm : connectedModules)
        cm->updateValues();
    
    process();
}

void NNModule::callReset() {
    alreadyUpdated = false;
    reset();
}