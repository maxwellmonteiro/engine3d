#include "Engine3dUtil.h"
#include "Matrix3d.h"

Vertice3d Engine3dUtil::calcNormal(Vertice3d& v0, Vertice3d& v1, Vertice3d& v2) {		
	
	
	Vertice3d line1 = v1 - v0;
	Vertice3d line2 = v2 - v0;

	// cross product
	Vertice3d normal = line1.crossProduct(line2);

	// normalize
	normal.normalize();

	return normal;
}

// Normalized dot product
float Engine3dUtil::calcDotProduct(Vertice3d& normal, Vertice3d& vertice, Vertice3d& camera) {
	float ret;
	
	Vertice3d vNormalized = vertice - camera;
	ret = normal.dotProduct(vNormalized);	

	return ret;
}

Vertice3d Engine3dUtil::calcProjectedVertice(Vertice3d& in, Matrix& projection) {
	Vertice3d out;
	Matrix3d vertice(1, 4);

	vertice.initVertice(in.x, in.y, in.z);
	Matrix projected = vertice * projection;

	out.x = projected(0, 0);
	out.y = projected(0, 1);
	out.z = projected(0, 2);

	float w = projected(0, 3);

	if (w != 0) {
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}
	return out;
}
