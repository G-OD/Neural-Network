#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cmath>
#include "Matrix.hpp"

class NeuralNetwork {
	int inputs;
	int hidden;
	int outputs;

	double learningRate;

public:

	Matrix *weights_ih;
	Matrix *weights_ho;
	Matrix *bias_h;
	Matrix *bias_o;
	NeuralNetwork(int inputs, int hidden, int outputs, double learningRate);

	static double sigmoid(double x);
	static double dsigmoid(double x);
	static double relu(double x);
	static double drelu(double x);

	Matrix feedforward(double inputArray[], int arrayLen);
	void train(std::vector<double> inputVector, std::vector<double> targetVector);
};

#endif