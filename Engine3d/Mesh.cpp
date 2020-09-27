#include "Mesh.h"

#include <fstream>
#include <sstream>

void Mesh::loadCube() {
	this->triangles = {

		// SOUTH
		{ Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f) },
		{ Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice3d(1.0f, 0.0f, 0.0f) },

		// EAST                                                      
		{ Vertice3d(1.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f) },
		{ Vertice3d(1.0f, 0.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(1.0f, 0.0f, 1.0f) },

		// NORTH                                                     
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f) },
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(0.0f, 0.0f, 1.0f) },

		// WEST                                                      
		{ Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(0.0f, 1.0f, 0.0f) },
		{ Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(0.0f, 0.0f, 0.0f) },

		// TOP                                                       
		{ Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(0.0f, 1.0f, 1.0f), Vertice3d(1.0f, 1.0f, 1.0f) },
		{ Vertice3d(0.0f, 1.0f, 0.0f), Vertice3d(1.0f, 1.0f, 1.0f), Vertice3d(1.0f, 1.0f, 0.0f) },

		// BOTTOM                                                    
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 0.0f) },
		{ Vertice3d(1.0f, 0.0f, 1.0f), Vertice3d(0.0f, 0.0f, 0.0f), Vertice3d(1.0f, 0.0f, 0.0f) }

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
				this->triangles.push_back({ cache[v1i - 1], cache[v2i - 1], cache[v3i - 1] });
			}
		}
		file.close();

		return true;
	}
	return false;
}
