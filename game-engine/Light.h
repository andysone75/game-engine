#ifndef LIGHT_H
#define LIGHT_H

class Light : public Component {
public:
	Light(glm::vec3 color);
	glm::vec3 getColor();

private:
	glm::vec3 color;
};

Light::Light(glm::vec3 color) {
	this->color = color;
}

glm::vec3 Light::getColor() {
	return color;
}

#endif
