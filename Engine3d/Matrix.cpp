#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
	//matrix = new float [rows * cols];		
	this->rows = rows;
	this->cols = cols;

	this->init();
}
/*
Matrix::~Matrix() {	
	delete [] matrix;
}
*/
float& Matrix::operator()(int row, int col) {
	return matrix[row * cols + col];
}

Matrix* Matrix::operator*(Matrix& m) {
	float soma;
	Matrix* ret = new Matrix(this->rows, m.cols);
	for (int i = 0; i < rows; i++) {		
		for (int k = 0; k < m.cols; k++) {
			soma = 0;
			for (int j = 0; j < m.rows; j++) {
				soma += matrix[i * cols + j] * m(j, k);
			}
			(*ret)(i, k) = soma;
		}		
	}	
	return ret;
}

void Matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << std::fixed << std::setw(11) << std::setprecision(2) << std::setfill(' ') << matrix[i * cols + j] << " ";			
		}
		std::cout << std::endl;
	}
}

void Matrix::init() {	
	for (int i = 0; i < rows * cols; i++) {		
		matrix[i] = 0.0f;		
	}
}

