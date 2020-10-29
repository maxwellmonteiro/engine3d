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

void Triangle::copyTexture(Triangle& t) {
	this->textures[0] = t.textures[0];
	this->textures[1] = t.textures[1];
	this->textures[2] = t.textures[2];
}

int Triangle::clip(Vertice3d planeP, Vertice3d planeN, Triangle& outTriangle1, Triangle& outTriangle2) {
	planeN.normalize();	

	Vertice3d* insidePoints[3];
	Vertice3d* outsidePoints[3];
	Vertice2d* insideTex[3];
	Vertice2d* outsideTex[3];
	int insidePointsCount = 0;
	int outsidePointsCount = 0;
	int insideTexCount = 0;
	int outsideTexCount = 0;

	// distance of eache point in triangle to plane
	float d0 = distance(this->vertices[0], planeP, planeN);
	float d1 = distance(this->vertices[1], planeP, planeN);
	float d2 = distance(this->vertices[2], planeP, planeN);

	if (d0 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[0];
		insideTex[insideTexCount++] = &this->textures[0];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[0];
		outsideTex[outsideTexCount++] = &this->textures[0];
	}
	if (d1 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[1];
		insideTex[insideTexCount++] = &this->textures[1];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[1];
		outsideTex[outsideTexCount++] = &this->textures[1];
	}
	if (d2 >= 0) {
		insidePoints[insidePointsCount++] = &this->vertices[2];
		insideTex[insideTexCount++] = &this->textures[2];
	}
	else {
		outsidePoints[outsidePointsCount++] = &this->vertices[2];
		outsideTex[outsideTexCount++] = &this->textures[2];
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
		float t;
		outTriangle1.vertices[0] = *insidePoints[0];
		outTriangle1.textures[0] = *insideTex[0];
		outTriangle1.vertices[1] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[0], t);
		outTriangle1.textures[1] = Vertice2d::intersect(*insideTex[0], *outsideTex[0], t);
		outTriangle1.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[1], t);
		outTriangle1.textures[2] = Vertice2d::intersect(*insideTex[0], *outsideTex[1], t);
		outTriangle1.copyRGB(*this);				
		return 1;
	} else if (insidePointsCount == 2 && outsidePointsCount == 1) {		
		float t;
		outTriangle1.vertices[0] = *insidePoints[0];
		outTriangle1.textures[0] = *insideTex[0];
		outTriangle1.vertices[1] = *insidePoints[1];		
		outTriangle1.textures[1] = *insideTex[1];
		outTriangle1.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[0], *outsidePoints[0], t);
		outTriangle1.textures[2] = Vertice2d::intersect(*insideTex[0], *outsideTex[0], t);
		
		outTriangle2.vertices[0] = *insidePoints[1];
		outTriangle2.textures[0] = *insideTex[1];
		outTriangle2.vertices[1] = outTriangle1.vertices[2];
		outTriangle2.textures[1] = outTriangle1.textures[2];
		outTriangle2.vertices[2] = Vertice3d::intersect(planeP, planeN, *insidePoints[1], *outsidePoints[0], t);
		outTriangle2.textures[2] = Vertice2d::intersect(*insideTex[1], *outsideTex[0], t);

		outTriangle1.copyRGB(*this);
		outTriangle2.copyRGB(*this);
		return 2;
	}
	return 0;
}

// Shortest distance from point to plane
float Triangle::distance(Vertice3d p, Vertice3d& planeP, Vertice3d& planeN) {	
	return (planeN.x * p.x + planeN.y * p.y + planeN.z * p.z - planeN.dotProduct(planeP));
}
