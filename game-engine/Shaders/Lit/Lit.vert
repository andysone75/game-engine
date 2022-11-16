#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	fragPos = (model * vec4(pos, 1.0)).xyz;
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragUv = uv;

//	vertexPos += normal * 0.5;
//	gl_Position = projection * view * vec4(vertexPos, 1.0);
}