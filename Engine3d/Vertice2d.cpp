#include "Vertice2d.h"

Vertice2d::Vertice2d() : Vertice2d(0.0f, 0.0f) {

}

Vertice2d::Vertice2d(float u, float v) {
	this->u = u;
	this->v = v;
}

Vertice2d Vertice2d::intersect(const Vertice2d& inside, const Vertice2d& outside, const float t) {
	Vertice2d ret;

	ret.u = t * (outside.u - inside.u) + inside.u;
	ret.v = t * (outside.v - inside.v) + inside.v;

	return ret;
}
