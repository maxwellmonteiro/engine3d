#include "Vertice3d.h"
#include <math.h>

Vertice3d::Vertice3d() : Vertice3d(0.0f, 0.0f, 0.0f) {

}

Vertice3d::Vertice3d(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
}

void Vertice3d::setRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Vertice3d Vertice3d::operator-(const Vertice3d& v) {	
	Vertice3d ret;

	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	ret.z = this->z - v.z;

	return ret;
}

Vertice3d Vertice3d::operator+(const Vertice3d& v) {
	Vertice3d ret;

	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	ret.z = this->z + v.z;

	return ret;
}

Vertice3d Vertice3d::operator*(const float v) {
	Vertice3d ret;

	ret.x = this->x * v;
	ret.y = this->y * v;
	ret.z = this->z * v;

	return ret;
}

// Cross product
Vertice3d Vertice3d::crossProduct(const Vertice3d& v) {	
	Vertice3d ret;

	ret.x = this->y * v.z - this->z * v.y;
	ret.y = this->z * v.x - this->x * v.z;
	ret.z = this->x * v.y - this->y * v.x;

	return ret;
}

// Dot product
float Vertice3d::dotProduct(const Vertice3d& v) {	
	return this->x * (v.x) + this->y * (v.y) + this->z * (v.z);	
}

void Vertice3d::normalize() {
	float n;
	n = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x /= n;
	this->y /= n;
	this->z /= n;
}
