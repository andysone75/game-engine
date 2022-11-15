#version 330 core

struct Material {
	vec3 diffuse;
}; 

in vec3 vertexColor;
out vec4 FragColor;

uniform Material material;

void main() {
	FragColor = vec4(material.diffuse, 1.0);
}
