#include "Mesh.h"
#include "Macros.h"

#include <fstream>
#include <sstream>

void Mesh::loadCube() {
	this->triangles = {

		{ Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice3d(1.0f, 0.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
                                                   
		{ Vertice3d(1.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(1.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(1.0f, 0.0f, 1.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
                                                   
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(0.0f, 0.0f, 1.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
                                                    
		{ Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(0.0f, 1.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(0.0f, 0.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
                                                     
		{ Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
                                               
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) },
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(1.0f, 0.0f, 0.0f), Vertice2d(0.0f, 1.0f), Vertice2d(0.0f, 0.0f), Vertice2d(1.0f, 0.0f) }

	};
}

bool Mesh::loadFromFile(std::string fileName) {
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::vector<Vertice3d> cache;

		char line[255];		
		char temp;
		while (!file.eof()) {
			std::stringstream str;			

			file.getline(line, sizeof(line));
			str << line;
			if (line[0] == 'v') {
				Vertice3d vertice;
				str >> temp >> vertice.x >> vertice.y >> vertice.z;
				cache.push_back(vertice);
			} else if (line[0] == 'f') {
				int v1i, v2i, v3i;
				str >> temp >> v1i >> v2i >> v3i;				
				this->triangles.push_back({ cache[castInt64(v1i) - 1], cache[castInt64(v2i) - 1], cache[castInt64(v3i) - 1] });
			}
		}
		file.close();

		return true;
	}
	return false;
}
