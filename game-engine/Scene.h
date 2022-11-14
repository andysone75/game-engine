#ifndef SCENE_H
#define SCENE_H

#include <array>

static void GeneratePolyNormals(std::vector<Vertex>& vertices, std::vector<Triangle>& tris);
static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<Triangle> tris);

class Scene {
public:
	Scene();

	std::vector<GameObject*> gameObjects = std::vector<GameObject*>();
	std::vector<Shader*> shaders;
	GameObject* light;

	void update(float dt);

private:
	GameObject* createGameObject();
};

Scene::Scene() {

	Shader* shaderLit = new Shader("Shaders/Lit/Lit.vert", "Shaders/Lit/Lit.frag");
	Shader* shaderDefault = new Shader("Shaders/Default/Default.vert", "Shaders/Default/Default.frag");
	shaders.push_back(shaderLit);
	shaders.push_back(shaderDefault);

	Mesh cubeMesh = geometry::createCube();
	GeneratePolyNormals(cubeMesh.vertices, cubeMesh.triangles);

	Mesh icoSphereMesh2 = geometry::createIcosphere(2);
	GeneratePolyNormals(icoSphereMesh2.vertices, icoSphereMesh2.triangles);

	Mesh icoSphereMesh5 = geometry::createIcosphere(5);
	GeneratePolyNormals(icoSphereMesh5.vertices, icoSphereMesh5.triangles);

	GameObject* light = createGameObject();
	light->addComponent(new MeshRenderer(icoSphereMesh2, shaderDefault));
	light->addComponent(new Light(glm::vec3(1.0f, 1.0f, 0.78f)));
	light->scale = glm::vec3(.3f);
	light->position = glm::vec3(0.0f, 3.0f, 0.0f);

	GameObject* ground = createGameObject();
	ground->addComponent(new MeshRenderer(cubeMesh, shaderLit));
	ground->position = glm::vec3(0.0f, -1.5f, 0.0f);
	ground->scale = glm::vec3(8.0f, 0.1f, 8.0f);

	GameObject* cube = createGameObject();
	cube->addComponent(new MeshRenderer(cubeMesh, shaderLit));
	cube->position = glm::vec3(-3.0f, 0.0f, 0.0f);
	cube->scale = glm::vec3(1.5f);

	GameObject* uvSphere = createGameObject();
	uvSphere->addComponent(new MeshRenderer(icoSphereMesh5, shaderLit));

	GameObject* icoSphere = createGameObject();
	icoSphere->addComponent(new MeshRenderer(icoSphereMesh2, shaderLit));
	icoSphere->position = glm::vec3(3.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->getComponent<Light>() != NULL) {
			this->light = gameObjects[i];
			break;
		}
	}
}

void Scene::update(float dt) {
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(dt);
	}
}

GameObject* Scene::createGameObject() { 
	GameObject* gameObject = new GameObject();
	gameObjects.push_back(gameObject);
	return gameObject;
}

static void GeneratePolyNormals(std::vector<Vertex>& vertices, std::vector<Triangle>& tris) {
	std::vector<Vertex> newVertices;
	std::vector<Triangle> newTris;
	for (int i = 0; i < tris.size(); i++)
	{
		Vertex a = vertices[tris[i].i0];
		Vertex b = vertices[tris[i].i1];
		Vertex c = vertices[tris[i].i2];

		glm::vec3 ab = b.getPosition() - a.getPosition();
		glm::vec3 ac = c.getPosition() - a.getPosition();
		glm::vec3 n = glm::normalize(glm::cross(ac, ab));

		vertices[tris[i].i0].normal = Vector3Float(n);
		vertices[tris[i].i1].normal = Vector3Float(n);
		vertices[tris[i].i2].normal = Vector3Float(n);

		a.normal = Vector3Float(n);
		b.normal = Vector3Float(n);
		c.normal = Vector3Float(n);

		newVertices.push_back(a);
		newVertices.push_back(b);
		newVertices.push_back(c);

		newTris.push_back(Triangle(i * 3 + 0, i * 3 + 1, i * 3 + 2));
	}
	vertices = newVertices;
	tris = newTris;
}

static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<Triangle> tris) {
	std::vector<std::vector<glm::vec3>> vertexNormals = std::vector<std::vector<glm::vec3>>(vertices.size());

	for (int i = 0; i < tris.size(); i++)
	{
		Vertex a = vertices[tris[i].i0];
		Vertex b = vertices[tris[i].i1];
		Vertex c = vertices[tris[i].i2];

		glm::vec3 ab = b.getPosition() - a.getPosition();
		glm::vec3 ac = c.getPosition() - a.getPosition();
		glm::vec3 n = glm::cross(ac, ab);

		vertexNormals[tris[i].i0].push_back(n);
		vertexNormals[tris[i].i1].push_back(n);
		vertexNormals[tris[i].i2].push_back(n);
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec3 normal = glm::vec3(0.0f);
		for (int j = 0; j < vertexNormals[i].size(); j++) {
			normal += vertexNormals[i][j];
		}
		normal = glm::normalize(normal);
		vertices[i].normal = Vector3Float(normal);
	}
}

#endif
