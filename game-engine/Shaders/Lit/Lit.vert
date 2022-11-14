#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 vertexPos;
out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	vertexPos = (model * vec4(pos, 1.0)).xyz;
	vertexColor = color;
	vertexNormal = mat3(transpose(inverse(model))) * normal;
}