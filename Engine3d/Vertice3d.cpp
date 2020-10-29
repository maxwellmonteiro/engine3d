#include "Vertice3d.h"
#include "Matrix3d.h"

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

Vertice3d Vertice3d::operator*(Matrix& matrix) {	
	Vertice3d out;
	Matrix3d vertice(1, 4);

	vertice.initVertice(this->x, this->y, this->z);
	Matrix projected = vertice * matrix;

	out.x = projected(0, 0);
	out.y = projected(0, 1);
	out.z = projected(0, 2);
	out.w = projected(0, 3);
	
	return out;	
}

Vertice3d Vertice3d::operator/(const float v) {
	Vertice3d ret;

	ret.x = this->x / v;
	ret.y = this->y / v;
	ret.z = this->z / v;

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

/** Calculete where a line insersect a plane. 
	planeP = point int the plane, 
	planeN = normal to the plane,
*/
Vertice3d Vertice3d::intersect(Vertice3d& planeP, Vertice3d& planeN, Vertice3d& lineStart, Vertice3d& lineEnd, float& t) {
	planeN.normalize();
	float planeD = -planeN.dotProduct(planeP);
	float ad = lineStart.dotProduct(planeN);
	float bd = lineEnd.dotProduct(planeN);
	t = (-planeD - ad) / (bd - ad);
	Vertice3d lineStartToEnd = lineEnd - lineStart;
	Vertice3d lineToIntersect = lineStartToEnd * t;
	return lineStart + lineToIntersect;
}