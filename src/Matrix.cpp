#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	
	this->data = new double*[rows];
	for (int i = 0; i < rows; i++)
		this->data[i] = new double[cols]();
}

Matrix::Matrix(const Matrix &matrix) {
	rows = matrix.rows;
	cols = matrix.cols;

	data = new double*[rows];
	for (int i = 0; i < rows; i++) {
		data[i] = new double[cols];
		for (int j = 0; j < cols; j++)
			data[i][j] = matrix.data[i][j];
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++)
		delete[] data[i];
	delete[] data;
}

void Matrix::print() {
	if (rows == 0 || cols == 0)
		std::cout << "Error. Empty matrix." << std::endl;

	std::cout << "[";
	for (int i = 0; i < rows; i++) {
		std::cout << "[";
		for (int j = 0; j < cols; j++) {
			std::cout << data[i][j];
			if (j < cols - 1) {
				std::cout << ",";
			}
		}
		std::cout << "]";

		if (i < rows - 1) {
			std::cout << ",";
		}
	}
	std::cout << std::endl;
}

void Matrix::printToCode() {
	if (rows == 0 || cols == 0)
		std::cout << "Error. Empty matrix." << std::endl;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			std::cout << "data[" << i << "]" << "[" << j << "]" << " = " << data[i][j] << ";" << std::endl;
}

Matrix Matrix::fromArray(double array[], int arrayLen)  {
	Matrix result = Matrix(arrayLen, 1);
	for (int i = 0; i < arrayLen; i++)
		result.data[i][0] = array[i];
	return result;
}

Matrix Matrix::fromVector(std::vector<double> vec)  {
	Matrix result = Matrix(vec.size(), 1);
	for (int i = 0; i < (int)vec.size(); i++)
		result.data[i][0] = vec[i];
	return result;
}

void Matrix::randomize() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			data[i][j] = ((double)std::rand() / RAND_MAX) * 2 - 1;
}

void Matrix::add(Matrix matrix) { 
	if (rows < matrix.rows || cols < matrix.cols) {
		std::cout << "Hadamard: Matrices do not match dimensions" << std::endl;
		return;
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			data[i][j] += matrix.data[i][j];
}

Matrix Matrix::subtract(Matrix a, Matrix b) {
	if (a.rows != b.rows || a.cols != b.cols) {
		std::cout << "Subtract: Matrices do not match dimensions" << std::endl;
		return Matrix(0, 0);
	}

	Matrix result = Matrix(a.rows, a.cols);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			result.data[i][j] = a.data[i][j] - b.data[i][j];
	return result;
}

// Hadamard product
void Matrix::hadamard(Matrix matrix) {
	if (rows != matrix.rows || cols != matrix.cols) {
		std::cout << "Hadamard: Matrices do not match dimensions" << std::endl;
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			data[i][j] *= matrix.data[i][j];
		}
	}
}

// Scalar product
void Matrix::scalar(double number) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			data[i][j] *= number;
}

// Dot product
Matrix Matrix::dot(Matrix *a, Matrix *b) {
	if (a->cols != b->rows) {
		std::cout << "Dot product: Columns must match rows" << std::endl;
		return Matrix(0, 0);
	}

	Matrix result = Matrix(a->rows, b->cols);
	
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			double sum = 0;
			for (int k = 0; k < a->cols; k++)
				sum += a->data[i][k] * b->data[k][j];
			result.data[i][j] = sum;
		}
	}

	return result;
}

Matrix Matrix::map(Matrix matrix, double (*f)(double number)) {
	Matrix result = Matrix(matrix.rows, matrix.cols);
	for (int i = 0; i < matrix.rows; i++)
		for (int j = 0; j < matrix.cols; j++)
			result.data[i][j] = f(matrix.data[i][j]);
	return result;
}

void Matrix::map(double (*f)(double number)) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			data[i][j] = f(data[i][j]);
}

Matrix Matrix::transpose(Matrix matrix) {
	Matrix result = Matrix(matrix.cols, matrix.rows);
	for (int i = 0; i < matrix.rows; i++)
		for (int j = 0; j < matrix.cols; j++)
			result.data[j][i] = matrix.data[i][j];
	return result;
}