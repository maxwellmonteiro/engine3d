#pragma once

#include <iostream>
#include <iomanip>

class Matrix {
	private:
		int rows, cols;		

		static void init(Matrix* matrix);

	public:
		float** matrix;
		Matrix(int rows, int cols);
		~Matrix();		
		Matrix* operator*(const Matrix& m);
		static Matrix* getProjection(float aspectRatio, float fieldView, float zNear, float zFar);
		static Matrix* getVertice(float x, float y, float z);
		void print();
};


