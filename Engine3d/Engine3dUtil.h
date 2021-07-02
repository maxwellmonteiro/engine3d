#pragma once

#include "Vertice3d.h"
#include "Matrix.h"
#include "Matrix3d.h"

class Engine3dUtil {
	public:
		static Vertice3d calcNormal(Vertice3d& v0, Vertice3d& v1, Vertice3d& v2);
		static float calcDotProduct(Vertice3d& normal, Vertice3d& vertice, Vertice3d& camera);
		static Vertice3d calcProjectedVertice(Vertice3d& in, Matrix& projection);
		static Matrix3d calcPointAt(Vertice3d& position, Vertice3d& target, Vertice3d& up);
		static Matrix3d createIdentity();
		static Matrix3d createTranslation(float x, float y, float z);
};

