#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <glad/glad.h>
#include "Shader.h"

class MeshRenderer : public Component {
public:
	Mesh* mesh;
	Material* material;

	MeshRenderer(Mesh* mesh, Material* material);
	void Draw();
};

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) {
	this->mesh = mesh;
	this->material = material;
}

void MeshRenderer::Draw() {
	material->getShader()->use();
	mesh->Draw();
}

#endif
