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

Matrix3d Engine3dUtil::calcPointAt(Vertice3d& position, Vertice3d& target, Vertice3d& up) {	
	// Calc new forward direction
	Vertice3d forward = target - position;
	forward.normalize();
	// Calc new up direction
	Vertice3d temp = forward * up.dotProduct(forward);
	Vertice3d newUp = up - temp;
	newUp.normalize();
	// Calc new right
	Vertice3d newRight = newUp.crossProduct(forward);
	// Fill point at matrix	
	Matrix3d matrix(4, 4);
	matrix(0, 0) = newRight.x;
	matrix(0, 1) = newRight.y;
	matrix(0, 2) = newRight.z;
	matrix(0, 3) = 0.0f;
	matrix(1, 0) = newUp.x;
	matrix(1, 1) = newUp.y;
	matrix(1, 2) = newUp.z;
	matrix(1, 3) = 0.0f;
	matrix(2, 0) = forward.x;
	matrix(2, 1) = forward.y;
	matrix(2, 2) = forward.z;
	matrix(2, 3) = 0.0f;
	matrix(3, 0) = position.x;
	matrix(3, 1) = position.y;
	matrix(3, 2) = position.z;
	matrix(3, 3) = 1.0f;
	return matrix;
}

Matrix3d Engine3dUtil::createIdentity() {
	Matrix3d matrix(4, 4);
	matrix(0, 0) = 1.0f;
	matrix(1, 1) = 1.0f;
	matrix(2, 2) = 1.0f;
	matrix(3, 3) = 1.0f;
	return matrix;
}

Matrix3d Engine3dUtil::createTranslation(float x, float y, float z) {
	Matrix3d matrix(4, 4);
	matrix(0, 0) = 1.0f;
	matrix(1, 1) = 1.0f;
	matrix(2, 2) = 1.0f;
	matrix(3, 3) = 1.0f;
	matrix(3, 0) = x;
	matrix(3, 1) = y;
	matrix(3, 2) = z;
	return matrix;
}
