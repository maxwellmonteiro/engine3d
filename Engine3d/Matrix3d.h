#pragma once
#include "Matrix.h"
class Matrix3d : public Matrix {
	public:
		Matrix3d(int rows, int cols);

		void initRotationZ(float theta);
		void initRotationX(float theta);
		void initRotationY(float theta);		
		void initProjection(float aspectRatio, float fieldView, float zNear, float zFar);
		void initVertice(float x, float y, float z);
		Matrix3d quickInvert();
};

