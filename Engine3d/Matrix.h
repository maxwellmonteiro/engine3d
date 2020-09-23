#pragma once

#include <iostream>
#include <iomanip>

class Matrix {
	private:
		int rows, cols;		

	public:
		float** matrix;
		Matrix(int rows, int cols);
		~Matrix();		
		Matrix* operator*(const Matrix& m);
		void print();
};


