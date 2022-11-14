#ifndef LIGHT_H
#define LIGHT_H

class Light : public Component {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light();
};

Light::Light() {
	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
}

#endif
