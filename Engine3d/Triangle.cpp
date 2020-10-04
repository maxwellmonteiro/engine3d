#include "Triangle.h"

void Triangle::setRGB(float r, float g, float b) {
	this->vertices[0].setRGB(r, g, b);
	this->vertices[1].setRGB(r, g, b);
	this->vertices[2].setRGB(r, g, b);
}

void Triangle::copyRGB(Triangle& t) {
	this->vertices[0].setRGB(t.vertices[0].r, t.vertices[0].g, t.vertices[0].b);
	this->vertices[1].setRGB(t.vertices[1].r, t.vertices[1].g, t.vertices[1].b);
	this->vertices[2].setRGB(t.vertices[2].r, t.vertices[2].g, t.vertices[2].b);
}

int Triangle::clip(Vertice3d planeP, Vertice3d planeN, Triangle& outTriangle1, Triangle& outTriangle2) {
	planeN.normalize();	

	Vertice3d* insidePoints[3];
	Vertice3d* outsidePoints[3];
	int insidePointsCount = 0;
	int outsidePointsCount = 0;

	// distance of eache point in triangle to plane
	float d0 = distance(this->vertices[0], planeP, planeN);
	float d1 = distance(this->vertices[1], planeP, planeN);
	float d2 = distance(this->vertices[2], planeP, planeN);

	if (d0 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[0];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[0];
	}
	if (d1 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[1];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[1];
	}
	if (d2 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[2];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[2];
	}

	// Classify an break the triangles
	if (insidePointsCount == 0) {
		// all points outside, remove the triangle
		return 0;
	} else if (insidePointsCount == 3) {
		// all points inside, keep the triangle
		outTriangle1 = *this;
		return 1;
	} else if (insidePointsCount == 1 && outsidePointsCount == 2) {
		outTriangle1.copyRGB(*this);

		outTriangle1.vertices[0] = *insidePoints[0];
		outTriangle1.vertices[1] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[0]);
		outTriangle1.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[1]);
		return 1;
	} else if (insidePointsCount == 2 && outsidePointsCount == 1) {
		outTriangle1.copyRGB(*this);
		outTriangle2.copyRGB(*this);

		outTriangle1.vertices[0] = *insidePoints[0];
		outTriangle1.vertices[1] = *insidePoints[1];
		outTriangle1.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[0]);
		
		outTriangle2.vertices[0] = *insidePoints[1];
		outTriangle2.vertices[1] = outTriangle1.vertices[2];
		outTriangle2.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[1], *outsidePoints[0]);
		return 2;
	}
}

// Shortest distance from point to plane
float Triangle::distance(Vertice3d p, Vertice3d& planeP, Vertice3d& planeN) {	
	return (planeN.x * p.x + planeN.y * p.y + planeN.z * p.z - planeN.dotProduct(planeP));
}
