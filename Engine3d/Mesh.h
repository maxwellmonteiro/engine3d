#pragma once

#include <vector>
#include <string>
#include "Triangle.h"

class Mesh {
	public:
		std::vector<Triangle> triangles;

		void loadCube();
		bool loadFromFile(std::string fileName);
};

