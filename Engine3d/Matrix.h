#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#define MAX_MATRIX_SIZE 4 * 4

class Matrix {
	protected:
		int rows, cols;		
		float matrix[MAX_MATRIX_SIZE];

		void init();
	public:		
		Matrix(int rows, int cols);		
		float& operator()(int row, int col);
		Matrix operator*(Matrix& m);				
		void print();		
};


