#pragma once

#include "Matrix.h"

class Vertice3d {
	public:
		float x, y, z;
		float w = 1.0f;
		float r, g, b;

		Vertice3d();
		Vertice3d(float x, float y, float z);		
		void setRGB(float r, float g, float b);
		Vertice3d operator-(const Vertice3d& v);
		Vertice3d operator+(const Vertice3d& v);
		Vertice3d operator*(const float v);
		Vertice3d operator*(Matrix& matrix);
		Vertice3d operator/(const float v);
		Vertice3d crossProduct(const Vertice3d& v);
		float dotProduct(const Vertice3d& v);
		void normalize();
		static Vertice3d intersect(Vertice3d& planeP, Vertice3d& planeN, Vertice3d& lineStart, Vertice3d& lineEnd);
};

