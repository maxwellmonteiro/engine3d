#pragma once

#include <vector>

struct vertice3d {
	float x, y, z;
};

struct triangle {
	vertice3d vertices[3];
};

struct mesh {
	std::vector<triangle> triangles;
};