#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 tangent;

	Vertex() = default;
	Vertex(glm::vec3 position) { this->position = position; }
};

struct Triangle {
public:
	unsigned int i0;
	unsigned int i1;
	unsigned int i2;

	Triangle() {
		i0 = 0;
		i1 = 0;
		i2 = 0;
	}

	Triangle(unsigned int i0, unsigned int i1, unsigned int i2) {
		this->i0 = i0;
		this->i1 = i1;
		this->i2 = i2;
	}
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	Mesh() = default;
	Mesh(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles);

	void Draw();

private:
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles) {
	this->vertices = vertices;
	this->triangles = triangles;
	setupMesh();
}

void Mesh::Draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle), triangles.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glBindVertexArray(0);
}

class Model {
public:
	Model(const char* path) {
		loadModel(path);
	}

	Model(Mesh mesh) {
		meshes.push_back(mesh);
	}

	Mesh* getMesh(unsigned int meshIndex);
	unsigned int getMeshesCount();
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

Mesh* Model::getMesh(unsigned int meshIndex) {
	return &meshes[meshIndex];
}

unsigned int Model::getMeshesCount() {
	return meshes.size();
}

void Model::loadModel(std::string path) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR:ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];
		aiVector3D uv = mesh->mTextureCoords[0][i];
		aiVector3D tangent = mesh->mTangents[i];

		Vertex vertex = Vertex(glm::vec3(pos.x, pos.y, pos.z));
		vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
		vertex.uv = glm::vec2(uv.x, uv.y);
		vertex.tangent = glm::vec3(tangent.x, tangent.y, tangent.z);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		triangles.push_back(Triangle(face.mIndices[0], face.mIndices[1], face.mIndices[2]));
	}

	return Mesh(vertices, triangles);
}

#endif