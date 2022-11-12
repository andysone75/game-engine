#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	Mesh() = default;
	Mesh(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles);
};

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles) {
	this->vertices = vertices;
	this->triangles = triangles;
}

#endif
