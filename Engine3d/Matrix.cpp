#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {	
	this->rows = rows;
	this->cols = cols;	
	this->init();
}

float& Matrix::operator()(int row, int col) {
	return matrix[row * cols + col];
}

Matrix Matrix::operator*(Matrix& m) {
	float soma;
	Matrix ret(this->rows, m.cols);
	for (int i = 0; i < rows; i++) {		
		for (int k = 0; k < m.cols; k++) {
			soma = 0.0f;
			for (int j = 0; j < m.rows; j++) {				
				soma += matrix[i * cols + j] * m.matrix[j * m.cols + k]; // Could use operator()(i, j) here to access the elements, but indexing the array is faster and this is the most executed piece of code
			}			
			ret.matrix[i * m.cols + k] = soma;
		}		
	}	
	return ret;
}

void Matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << std::fixed << std::setw(11) << std::setprecision(2) << std::setfill(' ') << operator()(i, j) << " ";			
		}
		std::cout << std::endl;
	}
}

void Matrix::init() {	
	for (int i = 0; i < rows * cols; i++) {		
		matrix[i] = 0.0f;		
	}
}


