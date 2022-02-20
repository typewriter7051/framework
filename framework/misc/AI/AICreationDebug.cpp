#include "../framework/misc/AI/templates.h"
#include <iostream>
#include <random>

int ni = 10, no = ni;

void doSomeShit(float angle, int iterations) {

	// tan can't handle 90 degrees dumbass.
	if (angle == 1.57079632679) {

		std::cout << "you big stupid!";
		return;

	}

	float x = 1, y = 0;
	float nx, ny;
	float c = cos(angle);
	float t = tan(angle);

	for (int i = 0; i < iterations; i++) {

		nx = c * (x + y * t);
		ny = c * (y - x * t);

		x = nx;
		y = ny;

		std::cout << "(" << x << ", " << y << ")\n";

	}

}

float dataFunction(float input) {

	return -0.5 * input;

}

void setupRecordingFile(TrainingNeuralNetwork* nn) {

	std::vector<float> inputs, expectedOutputs;

	nn->startRecording("damn");

	for (int j = 0; j < 1000; j++) {

		std::mt19937 mt(j);

		inputs.clear();
		expectedOutputs.clear();

		for (int i = 0; i < ni; i++) {

			float dr = (mt() / float(mt.max()) - 0.5) * 1.5;

			inputs.push_back(dr);
			expectedOutputs.push_back(dataFunction(dr));

		}

		nn->captureNeuralNetwork(&inputs, &expectedOutputs);

	}

	nn->stopRecording();

}

void trainNN(TrainingNeuralNetwork* nn) {

	for (int n = ni; n < ni + no; n++) {

		nn->trainNeuralNetwork("damn", nn->getNeuron(n), 50, 10, 0.1);

	}
	
}

int main() {

	TrainingNeuralNetwork nn;
	nn = createConvolutionalNetwork(ni, no, 5, 0);
	nn.setupWeights(-1, 1);

	//doSomeShit(0.1, 8);

	nn.saveToFile("damn");
	nn.loadFromFile("damn");

	setupRecordingFile(&nn);

	std::vector<float> inputs, outputs;
	for (int i = 0; i < ni; i++) {
		std::mt19937 mt(i * 10);
		float j = (mt() / float(mt.max()) - 0.5) * 1.5;
		inputs.push_back(j);
		outputs.push_back(dataFunction(j));
	}

	std::cout << nn.getCost(&inputs, &outputs) << std::endl;
	trainNN(&nn);
	std::cout << nn.getCost(&inputs, &outputs) << std::endl;

	return 0;

}