#version 330 core

in vec3 vertexPos;
in vec3 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - vertexPos);
	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	float d = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = lightColor * d;
	
	vec3 color = vertexColor * (ambient + diffuse);

//	fragColor = vec4(vertexColor * (ambient + diffuse), 1.0);
	fragColor = vec4(color, 1.0);
}