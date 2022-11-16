#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(Shader* shader, Texture* diffuseTexture = NULL, GLenum diffuseTexFormat = GL_RGB) {
		this->shader = shader;
		this->diffuseTexture = 0;

		ambient = glm::vec3(1.0f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3(1.0f);
		shininess = 32.0f;

		if (diffuseTexture != NULL) {
			glGenTextures(1, &this->diffuseTexture);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, diffuseTexture->width, diffuseTexture->height, 0, diffuseTexFormat, GL_UNSIGNED_BYTE, diffuseTexture->data);
			glGenerateMipmap(GL_TEXTURE_2D);

			shader->use();
			shader->setInt("diffuseTexture", 0);
		}
	}

	Shader* getShader();
	void updateShader();
	void bindTextures();

private:
	Shader* shader;
	unsigned int diffuseTexture;
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
}

#endif