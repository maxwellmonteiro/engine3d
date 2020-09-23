#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
	matrix = new float* [rows];

	for (int i = 0; i < rows; i++) {
		matrix[i] = new float[cols];
	}

	this->rows = rows;
	this->cols = cols;
}

Matrix::~Matrix() {
	for (int i = 0; i < this->rows; i++) {
		delete [] matrix[i];
	}
	delete [] matrix;
}

Matrix* Matrix::operator*(const Matrix& m) {
	float soma;
	Matrix* ret = new Matrix(this->rows, m.cols);
	for (int i = 0; i < this->rows; i++) {		
		for (int k = 0; k < m.cols; k++) {
			soma = 0;
			for (int j = 0; j < m.rows; j++) {
				soma += matrix[i][j] * m.matrix[j][k];
			}
			ret->matrix[i][k] = soma;
		}		
	}
	return ret;
}

void Matrix::print() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			std::cout << std::fixed << std::setw(11) << std::setprecision(2) << std::setfill(' ') << matrix[i][j] << " ";			
		}
		std::cout << std::endl;
	}
}
