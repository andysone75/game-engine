#version 330 core

in vec3 vertexPos;
in vec3 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
	vec3 lightDir = normalize(lightPos - vertexPos);
	float d = dot(vertexNormal, lightDir);

	fragColor = vec4(vertexColor * lightColor * d, 1.0);
}