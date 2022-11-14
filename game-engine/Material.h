#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(Shader* shader) {
		this->shader = shader;

		ambient = glm::vec3(1.0f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3(1.0f);
		shininess = 32.0f;
	}

	Shader* getShader();
	void updateShader();

private:
	Shader* shader;
};

Shader* Material::getShader() {
	return shader;
}

void Material::updateShader() {
	shader->use();
	shader->setFloat3("material.ambient", ambient);
	shader->setFloat3("material.diffuse", diffuse);
	shader->setFloat3("material.specular", specular);
	shader->setFloat("material.shininess", shininess);
}

#endif