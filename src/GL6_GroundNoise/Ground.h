#ifndef GROUND_H
#define GROUND_H

#include <vector>
#include "../include/Mesh.h"

class Ground
{
public:
	Ground();
	Ground(int x, int z) : _x(x), _z(z) {};
	Ground(int x, int z, float sizeX, float sizeZ) : _x(x), _z(z), _sizeX(sizeX), _sizeZ(sizeZ) {};

	Mesh* createMesh()
	{
		Mesh* mesh;
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;

		for(int i = 0 ; i < _z; ++i)
		{
			for(int j =  0 ; j < _x ; ++j)
			{
				Vertex v;
				v.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
				v.TexCoords = glm::vec2(static_cast<float>(j & 1), static_cast<float>(i & 1));
				v.Position = glm::vec3(j * _sizeX, 0.0f, i * _sizeZ);
				vertices.push_back(v);
			}
		}

		for(int i = 0 ; i < _z - 1; ++i)
		{
			for (int j = 0; j < _x - 1; ++j)
			{
				int pos1, pos2, pos3;

				pos1 = j + i * _x;
				pos2 = j + 1 + i * _x;
				pos3 = j + (i + 1) * _x;
				
				indices.push_back(pos1);
				indices.push_back(pos2);
				indices.push_back(pos3);

				pos1 = j + 1 + (i + 1) * _x;
				pos2 = j + (i + 1) * _x;
				pos3 = j + 1 + i * _x;

				indices.push_back(pos1);
				indices.push_back(pos2);
				indices.push_back(pos3);
				
			}
		}
		
		return new Mesh(vertices, indices);
	}
	
private:
	int _x = 10;
	int _z = 10;
	float _sizeX = 1;
	float _sizeZ = 1;
	
};

#endif // GROUND_H