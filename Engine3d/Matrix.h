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
		void init();
		void print();
		static void initProjection(Matrix& matrix, float aspectRatio, float fieldView, float zNear, float zFar);
		static void initVertice(Matrix& vertice, float x, float y, float z);
};


