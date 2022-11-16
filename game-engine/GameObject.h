#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

class GameObject {
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	std::vector<Component*> components = std::vector<Component*>();

	void update(float dt);
	GameObject* addComponent(Component* component);
	glm::mat4 getTransform();
	
	template<class T>
	T* getComponent();

private:
	glm::mat4 transform = glm::mat4(1.0f);
	float timer;
};

void GameObject::update(float dt) {
	timer += dt;
	transform = glm::translate(glm::mat4(1.0f), position);
	//transform = glm::rotate(transform, -glm::pi<float>() / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//transform = glm::rotate(transform, timer * .35f, glm::vec3(0.58f));
	transform = glm::rotate(transform, timer * .1f, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, scale);
}

GameObject* GameObject::addComponent(Component* component) {
	components.push_back(component);
	return this;
}

glm::mat4 GameObject::getTransform() {
	return transform;
}

template<class T>
T* GameObject::getComponent() {
	for (size_t i = 0; i < components.size(); i++)
	{
		if (T* component = dynamic_cast<T*>(components[i])) {
			return component;
		}
	}
	return NULL;
}

#endif
