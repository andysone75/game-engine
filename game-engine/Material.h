#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(Shader* shader, Texture* diffuseTexture = NULL, Texture* normalTexture = NULL) {
		this->shader = shader;
		this->diffuseTexture = 0;

		ambient = glm::vec3(1.0f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3(1.0f);
		shininess = 32.0f;

		if (diffuseTexture != NULL) {
			createTexture(&this->diffuseTexture, diffuseTexture, 0);
		}

		if (normalTexture != NULL) {
			createTexture(&this->normalTexture, normalTexture, 1);
		}
	}

	Shader* getShader();
	void updateShader();
	void bindTextures();

private:
	Shader* shader;
	unsigned int diffuseTexture;
	unsigned int normalTexture;

	void createTexture(unsigned int* ID, Texture* texture, int unitIndex);
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

void Material::bindTextures() {
	if (diffuseTexture > 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	}

	if (normalTexture > 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTexture);
	}
}

void Material::createTexture(unsigned int* ID, Texture* texture, int unitIndex) {
	glGenTextures(1, ID);
	glBindTexture(GL_TEXTURE_2D, *ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format;
	if (texture->channelsCount == 1)
		format = GL_RED;
	else if (texture->channelsCount == 3)
		format = GL_RGB;
	else if (texture->channelsCount == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	shader->use();
	shader->setInt("material." + (texture->type), unitIndex);
}

#endif