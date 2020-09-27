#pragma once
class Vertice3d {
	public:
		float x, y, z;
		float r, g, b;

		Vertice3d():Vertice3d(0.0f, 0.0f, 0.0f) {};
		Vertice3d(float x, float y, float z);
		~Vertice3d();
		void setRGB(float r, float g, float b);
		Vertice3d* operator-(const Vertice3d& v);
		Vertice3d* crossProduct(const Vertice3d& v);
		float dotProduct(const Vertice3d& v);
		void normalize();
};
