#include "Engine3dUtil.h"

Vertice3d* Engine3dUtil::calcNormal(Vertice3d& v0, Vertice3d& v1, Vertice3d& v2) {	
	Vertice3d* line1;
	Vertice3d* line2;
	Vertice3d* normal;
	
	line1 = v1 - v0;
	line2 = v2 - v0;

	// cross product
	normal = line1->crossProduct(*line2);
	delete line1;
	delete line2;

	// normalize
	normal->normalize();

	return normal;
}

// Normalized dot product
float Engine3dUtil::calcDotProduct(Vertice3d& normal, Vertice3d& vertice, Vertice3d& camera) {
	float ret;
	Vertice3d* vNormalized;

	vNormalized = vertice - camera;
	ret = normal.dotProduct(*vNormalized);

	delete vNormalized;

	return ret;
}
