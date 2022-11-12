#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <glad/glad.h>
#include "Shader.h"

class MeshRenderer : public Component {
public:
	unsigned int VAO;
	unsigned int indicesCount;
	Mesh mesh;
	Shader* shader;

	MeshRenderer(Mesh mesh, Shader* shader);
};

MeshRenderer::MeshRenderer(Mesh mesh, Shader* shader) {
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(Triangle), mesh.triangles.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	this->indicesCount = mesh.triangles.size() * 3;
	this->mesh = mesh;
	this->shader = shader;
}

#endif
