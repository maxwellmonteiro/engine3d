#pragma once

#include "Vertice3d.h"
#include "Matrix.h"

class Engine3dUtil {
	public:
		static Vertice3d* calcNormal(Vertice3d& v0, Vertice3d& v1, Vertice3d& v2);
		static float calcDotProduct(Vertice3d& normal, Vertice3d& vertice, Vertice3d& camera);
		static void initProjection(Matrix& matrix, float aspectRatio, float fieldView, float zNear, float zFar);
		static void initVertice(Matrix& vertice, float x, float y, float z);
};

