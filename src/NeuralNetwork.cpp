#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int inputs, int hidden, int outputs, double learningRate) {
	this->inputs = inputs;
	this->hidden = hidden;
	this->outputs = outputs;
	this->learningRate = learningRate;

	weights_ih = new Matrix(hidden, inputs);
	weights_ho = new Matrix(outputs, hidden);
	weights_ih->randomize();
	weights_ho->randomize();

	bias_h = new Matrix(hidden, 1);
	bias_o = new Matrix(outputs, 1);
	bias_h->randomize();
	bias_o->randomize();
}

double NeuralNetwork::sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

double NeuralNetwork::dsigmoid(double x) {
	// return sigmoid(x) * (1 - sigmoid(x));
	return x * (1 - x);
}

// double NeuralNetwork::relu(double x) {
// 	return log(1 + exp(x));
// }

// double NeuralNetwork::drelu(double x) {
// 	return (x < 0) ? 0 : 1;
// }

Matrix NeuralNetwork::feedforward(double inputArray[], int arrayLen) {
	Matrix inputs = Matrix::fromArray(inputArray, arrayLen);

	Matrix hidden = Matrix::dot(weights_ih, &inputs);
	hidden.add(*bias_h);
	hidden.map(sigmoid);

	Matrix outputs = Matrix::dot(weights_ho, &hidden);
	outputs.add(*bias_o);
	outputs.map(sigmoid);

	return outputs;
}

void NeuralNetwork::train(std::vector<double> inputVector, std::vector<double> targetVector) {
	// 
	Matrix inputs = Matrix::fromVector(inputVector);

	Matrix hidden = Matrix::dot(weights_ih, &inputs);
	hidden.add(*bias_h);
	hidden.map(sigmoid);

	Matrix outputs = Matrix::dot(weights_ho, &hidden);
	outputs.add(*bias_o);
	outputs.map(sigmoid);

	Matrix targets = Matrix::fromVector(targetVector);
	// 

	// Calculate errors
	Matrix outputErrors = Matrix::subtract(targets, outputs);

	// Gradients
	Matrix gradients = Matrix::map(outputs, dsigmoid);
	// Matrix gradients = Matrix(outputs);
	gradients.hadamard(outputErrors);
	gradients.scalar(learningRate);

	// Calculate deltas
	Matrix hidden_T = Matrix::transpose(hidden);
	Matrix weights_ho_deltas = Matrix::dot(&gradients, &hidden_T);
	// hidden_T.print();

	// Change weights by deltas
	weights_ho->add(weights_ho_deltas);
	bias_o->add(gradients);

	// // Calculate hidden errors
	Matrix whoT = Matrix::transpose(*weights_ho);
	Matrix hiddenErrors = Matrix::dot(&whoT, &outputErrors);

	// Gradients
	Matrix hiddenGradients = Matrix::map(hidden, dsigmoid);
	// Matrix hiddenGradients = Matrix(hidden);
	hiddenGradients.hadamard(hiddenErrors);
	hiddenGradients.scalar(learningRate);

	// Calculate deltas
	Matrix inputs_T = Matrix::transpose(inputs);;
	Matrix weights_ih_deltas = Matrix::dot(&hiddenGradients, &inputs_T);

	// Change weights by deltas
	weights_ih->add(weights_ih_deltas);
	bias_h->add(hiddenGradients);
}