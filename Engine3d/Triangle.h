#pragma once

#include "Vertice3d.h"

class Triangle {	
	private:
		float distance(Vertice3d p, Vertice3d& planeP, Vertice3d& planeN);
	public:
		Vertice3d vertices[3];
		void setRGB(float r, float g, float b);
		void copyRGB(Triangle& t);
		int clip(Vertice3d planeP, Vertice3d planeN, Triangle& outTriangle1, Triangle& outTriangle2);
};

