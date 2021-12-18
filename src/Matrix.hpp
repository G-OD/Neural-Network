#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
public:
	int rows;
	int cols;
	double **data;

	Matrix(int rows, int cols);

	Matrix(const Matrix &matrix);

	~Matrix();

	void print();
	void printToCode();

	static Matrix fromArray(double array[], int arrayLen);
	// static Matrix from2DArray(double array[], int arrayLen);
	static Matrix fromVector(std::vector<double> vec);

	void randomize();

	static Matrix subtract(Matrix a, Matrix b);
	void add(Matrix matrix);

	// Dot product
	static Matrix dot(Matrix *a, Matrix *b);
	// Hadamard product
	void hadamard(Matrix matrix);
	// Scalar product
	void scalar(double number);

	// Map to function
	static Matrix map(Matrix matrix, double (*f)(double number));
	void map(double (*f)(double number));

	static Matrix transpose(Matrix matrix);
};

#endif