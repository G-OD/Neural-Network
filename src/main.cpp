#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#include "NeuralNetwork.hpp"

typedef struct trainingItem {
	std::vector<double> inputs;
	std::vector<double> targets;
} trainingItem;

int main() {
	std::srand(std::time(NULL));

	std::vector<trainingItem> trainingData;

	trainingItem i;

	i.inputs.push_back(1);
	i.inputs.push_back(0);
	i.targets.push_back(1);
	trainingData.push_back(i);

	i.inputs.clear();
	i.targets.clear();

	i.inputs.push_back(0);
	i.inputs.push_back(0);
	i.targets.push_back(0);
	trainingData.push_back(i);

	i.inputs.clear();
	i.targets.clear();

	i.inputs.push_back(1);
	i.inputs.push_back(1);
	i.targets.push_back(0);
	trainingData.push_back(i);

	i.inputs.clear();
	i.targets.clear();

	i.inputs.push_back(0);
	i.inputs.push_back(1);
	i.targets.push_back(1);
	trainingData.push_back(i);


	NeuralNetwork nn = NeuralNetwork(2, 2, 1, 0.1);
	// nn.weights_ih->data[0][0] = -10.4546;
	// nn.weights_ih->data[0][1] = 10.8259;
	// nn.weights_ih->data[1][0] = -10.7374;
	// nn.weights_ih->data[1][1] = 10.3747;

	// nn.weights_ho->data[0][0] = -7.60165;
	// nn.weights_ho->data[0][1] = 7.82625;

	// nn.bias_h->data[0][0] = 5.28387;
	// nn.bias_h->data[1][0] = -5.34937;

	// nn.bias_o->data[0][0] = 3.67968;

	// Train
	for (int i = 0; i < 100000; i++) {
		trainingItem item = trainingData[std::rand() % trainingData.size()];
		nn.train(item.inputs, item.targets);
	}

	double array[] = {1, 1};
	nn.feedforward(array, 2).print();

	array[0] = 0;
	array[1] = 0;
	nn.feedforward(array, 2).print();

	array[0] = 1;
	array[1] = 0;
	nn.feedforward(array, 2).print();

	array[0] = 0;
	array[1] = 1;
	nn.feedforward(array, 2).print();

	printf("\n");

	nn.weights_ih->printToCode();
	nn.weights_ho->printToCode();
	nn.bias_h->printToCode();
	nn.bias_o->printToCode();
}
