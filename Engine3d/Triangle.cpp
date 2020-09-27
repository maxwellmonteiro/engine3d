#include "Triangle.h"

void Triangle::setRGB(float r, float g, float b) {
	this->vertices[0].setRGB(r, g, b);
	this->vertices[1].setRGB(r, g, b);
	this->vertices[2].setRGB(r, g, b);
}
