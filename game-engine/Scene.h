#ifndef SCENE_H
#define SCENE_H

#include <array>

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

	Mesh* cubeMesh = geometry::createCube();
	Model* cubeSphereModel = new Model("Models/cube_sphere.fbx");
	Model* hotdogModel = new Model("Models/hotdog.fbx");
	Model* shaderBallModel = new Model("Models/shader-ball/source/shader_ball.obj");

	int channelsCount;
	Texture shaderBallDiffuse;
	shaderBallDiffuse.data = stbi_load("Models/shader-ball/textures/ShaderBallJL01_BaseColor.jpeg", &shaderBallDiffuse.width, &shaderBallDiffuse.height, &channelsCount, 0);

	Material* lightMaterial = new Material(shaderDefault);
	Material* defaultMaterial = new Material(shaderLit);
	Material* shaderBallMaterial = new Material(shaderLit, &shaderBallDiffuse, GL_RGB);

	Material* emeraldMaterial = new Material(shaderLit);
	emeraldMaterial->ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
	emeraldMaterial->diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568);
	emeraldMaterial->specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	emeraldMaterial->shininess = 0.6f * 128.0f;

	Material* silverMaterial = new Material(shaderLit);
	silverMaterial->ambient = glm::vec3(0.19225f);
	silverMaterial->diffuse = glm::vec3(0.50754f);
	silverMaterial->specular = glm::vec3(0.508273f);
	silverMaterial->shininess = 0.4f * 128.0f;

	Material* plasticMaterial = new Material(shaderLit);
	plasticMaterial->ambient = glm::vec3(0.0f);
	plasticMaterial->diffuse = glm::vec3(0.55f);
	plasticMaterial->specular = glm::vec3(0.7f);
	plasticMaterial->shininess = 0.25f * 128.0f;
	
	stbi_image_free(shaderBallDiffuse.data);

	GameObject* light = createGameObject();
	light->addComponent(new MeshRenderer(cubeMesh, lightMaterial));
	light->addComponent(new Light());
	light->scale = glm::vec3(.3f);
	light->position = glm::vec3(0.0f, 3.0f, 0.0f);

	//GameObject* ground = createGameObject()
	//	->addComponent(new MeshRenderer(cubeMesh, defaultMaterial));
	//ground->position = glm::vec3(0.0f, -1.5f, 0.0f);
	//ground->scale = glm::vec3(8.0f, 0.1f, 8.0f);

	//GameObject* sphere = createGameObject()
	//	->addComponent(new MeshRenderer(cubeSphereModel->getMesh(0), emeraldMaterial));
	//sphere->scale = glm::vec3(0.7f);
	//sphere->position = glm::vec3(1.0f, 0.0f, 0.0f);

	//GameObject* hotdog = createGameObject()
	//	->addComponent(new MeshRenderer(hotdogModel->getMesh(0), plasticMaterial));
	//hotdog->scale = glm::vec3(0.05f);
	//hotdog->position = glm::vec3(-1.0f, 0.0f, 0.0f);

	//GameObject* hotdogSilver = createGameObject()
	//	->addComponent(new MeshRenderer(hotdogModel->getMesh(0), silverMaterial));
	//hotdogSilver->scale = glm::vec3(0.05f);
	//hotdogSilver->position = glm::vec3(0.0f, 0.0f, 0.0f);

	//GameObject* hotdogEmerald = createGameObject()
	//	->addComponent(new MeshRenderer(hotdogModel->getMesh(0), emeraldMaterial));
	//hotdogEmerald->scale = glm::vec3(0.05f);
	//hotdogEmerald->position = glm::vec3(1.0f, 0.0f, 0.0f);

	std::array<Material*, 1> shaderBallMaterials = {
		shaderBallMaterial,
	};

	float scale = 1.0f;
	glm::vec3 pos = glm::vec3(0.0f, 0.5f, -1.5f);
	for (unsigned int i = 0; i < shaderBallModel->getMeshesCount(); i++)
	{
		Material* mat;

		if (i >= shaderBallMaterials.size()) {
			mat = defaultMaterial;
		}
		else {
			mat = shaderBallMaterials[i];
		}

		GameObject* o = createGameObject()
			->addComponent(new MeshRenderer(shaderBallModel->getMesh(i), mat));
		o->scale = glm::vec3(scale);
		o->position = pos;
	}

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

#endif
